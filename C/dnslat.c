#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

#include <sys/socket.h>

#include <sys/time.h>

int main(int argc, char **argv)
{
    if (argc < 2)
        exit(1);
    struct timeval ts;
    time_t oldtime;
    time_t newtime;
    
    for (int i = 1; i < argc; i++)
    {
        gettimeofday(&ts, NULL);
        oldtime = ts.tv_usec;
        gethostbyname(argv[i]);

        gettimeofday(&ts, NULL);
        newtime = ts.tv_usec;

        printf("%s: %lf\n", argv[i], ((double)(newtime - oldtime)) / 1000.0);
    }
}
