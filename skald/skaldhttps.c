#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>

#include <curl/curl.h>

#include "skald.h"

const int HEARTBEAT = 30;

void usage(char *name) {
    printf("%s [-d] hostname http_path notify\n", name);
}

int mainloop(CURL *watcher, char *host, char *path, char *notify) {
    last_good_time = 0;

    bool sent_message = false;
    
    size_t url_len = strlen("http://") + strlen(host) + strlen(path) + 1;

    char *url = malloc(url_len);
    
    // Yes, snprintf makes sure you get the terminating null
    snprintf(url, url_len, "https://%s%s", host, path);

    curl_easy_setopt(watcher, CURLOPT_URL, url);

    curl_easy_setopt(watcher, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(watcher, CURLOPT_SSL_VERIFYHOST, 0L);
    while (true) {
        CURLcode result;
        time_t start_time;
        time(&start_time);


        result = curl_easy_perform(watcher);

        if (result == CURLE_OK){
            long respcode;
            curl_easy_getinfo(watcher, CURLINFO_RESPONSE_CODE, &respcode);

            if (respcode >= 200 && respcode < 400) {
                sent_message = false;
                time(&last_good_time);
            }
            else {
                printf("RESP: %ld\n", respcode);

                page_error(notify, url, sent_message);
                sent_message = true;

                printf("ded too\n");
            }
        }
        else {
            printf("ded\n");
            page_error(notify, url, sent_message);
            sent_message = true;
        }

        sleep(max(0, HEARTBEAT - (time(NULL) - start_time)));
    }

    curl_easy_cleanup(watcher);
    curl_global_cleanup();
    return 0;
}

int main(int argc, char **argv) {
    char *progname = argv[0];
    
    CURL *curl;

    bool daemonize = false;

    srand(time(NULL));
    
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
            return 0;
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

    printf("%s\n", argv[2]);
    return mainloop(curl, argv[1], argv[2], argv[3]);
}
