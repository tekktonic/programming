#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define BATPATH "/sys/class/power_supply/BAT0/capacity"
#define CHARGINGPATH "/sys/class/power_supply/AC/online"
#define max(x, y) (((x) > (y) ? (x) : (y)))

enum acstate
{
    NOT_CHARGING,
    CHARGING

};
struct battstate
{
    unsigned int percentage;
    enum acstate charging;
};

struct battstate read_battstate(void)
{
    FILE *fp;
    struct battstate ret;
    
    fp = fopen(BATPATH, "r");
    if (!fp)
    {
	fprintf(stderr, "Unable to open %s to read battery charge\n", BATPATH);
	exit(1);
    }
    fscanf(fp, "%ud3", &ret.percentage);
    fclose(fp);
    fp = fopen(CHARGINGPATH, "r");
    if (!fp)
    {
	fprintf(stderr, "Unable to open %s\n", BATPATH);
	exit(1);
    }
    fscanf(fp, "%ud1", &ret.charging);
    return ret;
}

void usage(void)
{
    printf("Usage: hibbert [-n -p percentage -t trigger -h -i interval]\nTrigger a script when battery reaches a certain percentage\n-i\tSpecify poll interval (seconds)\n-n\tDon't daemonize.\n-p\tSet percentage to trigger at.\n-t\tSet different trigger (defaults to ~/.hibbertt if it exists, /etc/hibbertt if not)\n");
}

int main(int argc, char *argv[])
{
    bool daemon = true;
    unsigned int triggerpercent = 5;
    unsigned int interval = 60; // 1 minute default poll time
    int triggerlen = max(strlen(getenv("HOME")) + strlen("/.hibbertt"), strlen("/etc/hibbertt")) + 1;
    char *trigger = malloc(triggerlen);
    *trigger = '\0';
    int lensize;
    int c;
    while ((c = getopt(argc, argv, "nhp:t:")) != -1)
    {
	switch (c)
	{
	case 'i':
	    sscanf(optarg, "%ud", &interval);
	    break;
	case 'n':
	    daemon = false;
	    break;
	case 'p':
	    sscanf(optarg, "%ud3", &triggerpercent);
	    break;
	case 't':
	    lensize = strlen(optarg) + 1;
	    if (lensize > triggerlen)
	    {
		triggerlen = lensize;
		trigger = realloc(trigger, triggerlen);
	    }
	    strncpy(trigger, optarg, triggerlen);
	    break;
	case 'h':
	    usage();
	    return 0;
	    break;
	}
    }
    if (daemon)
    {
	int p = fork();
	if (p != 0)
	    exit(1);

	if (setsid() < 0)
	    exit(1);
    }

    while (true)
    {
	struct battstate batt = read_battstate();
	if ((batt.percentage <= triggerpercent) && batt.charging != CHARGING)
	{
	    if (*trigger == '\0')
	    {
		snprintf(trigger, triggerlen, "%s/.hibbertt", getenv("HOME"));
		FILE *fp = fopen(trigger, "r");
		if (!fp)
		{
		    fprintf(stderr, "Unable to read ~/.hibbertt, trying system trigger\n");
		    fp = fopen("/etc/hibbertt", "r");
		    if (!fp)
		    {
			fprintf(stderr, "Unable to open /etc/hibbertt either! Exiting\n");
			return 1;
		    }
		    snprintf(trigger, triggerlen, "/etc/hibbertt");
		}
	    }
	    if (fork() == 0)		    
		execlp("/bin/sh", "-c", trigger, NULL);
	    
	}
	sleep(interval);
    }
    return 0;
}
