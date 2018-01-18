#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>

#include <curl/curl.h>

#define ORDIE(v, message) do{if (!(v)) {fprintf(stderr, message);}}while(0)

const int TENMINUTES = 600;
const int HEARTBEAT = 30;

void usage(char *name) {
    printf("%s [-d] hostname http_path notify", name);
}

int mainloop(CURL *watcher, char *host, char *path, char *notify) {
    size_t url_len = strlen("http://") + strlen(host) + strlen(path);
    char *url = malloc(url_len + 1);

    snprintf(url, url_len, "http://%s%s", host, path);

    printf("@%s: %s\n", notify, url);

    return 0;
}

int main(int argc, char **argv) {
    char *progname = argv[0];
    
    time_t last_good_time = 0;
    CURL *curl;

    bool daemonize = false;
    
    if (argc < 4) {
        usage(progname);
        return 1;
    }

    // This is safe because the 0th character exists even on an empty string, that character is NULL
    if ((argv[1])[0] == '-') {
        switch ((argv[1])[1]) {
        case 'd':
            daemonize = true;
        }

        // Shift all of the arguments 'backward' by one so that it looks like there was no argument given. argv[1] is still the host
        argv++;
        argc--;
    }

    // We mucked around with argv and argc, so we need to re-check
    if (argc < 4) {
        usage(progname);
        return 1;
    }
    
    ORDIE(curl_global_init(CURL_GLOBAL_DEFAULT) == 0, "Unable to initialize LibCURL.");
    ORDIE((curl = curl_easy_init()) != NULL, "Unable to create CURL instance.");

    /*
     * Daemonize the process, that is, make it run even when its running terminal is closed.
     * This is accomplished with a double fork, which isolates the running daemon process
     * from its running terminal.
     */
    if (daemonize) {
        int f1 = fork();
        if (f1 != 0) {
            if (f1 == -1)
                fprintf(stderr, "Unable to daemonize.");
        }

        // First fork done, do the second to take us out of the terminal's control.
        int f2 = fork();
        if (f2 != 0) {
            // Second fork failed but we're still under the terminal, so print an error.
            if (f2 == -1)
                fprintf(stderr, "Unable to daemonize.");
            return 0;
        }
    }

    return mainloop(curl, argv[1], argv[2], argv[3]);

}
