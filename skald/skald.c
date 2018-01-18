#include <curl/curl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "skald.h"

time_t last_good_time;

struct mail {
    int lines_sent;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int digits(uint64_t in) {
    int ret = 1;
    while (in != 0) {
        ret++;
        in /= 10;
    }

    return ret;
}

char *makedate(void) {
    time_t tmptime = time(NULL);
    struct tm *t = localtime(&tmptime);
    const char *days[] = {
        "Mon",
        "Tue",
        "Wed",
        "Thu",
        "Fri",
        "Sat",
        "Sun"
    };
    
    const char *months[] = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
    };
    
    // Not necessarily always monday, but length is right.
    size_t ret_len = strlen("Date: Mon, ") + digits(t->tm_mday)
        + strlen(" Jan 2017 00:00:00\r\n") + 1;
    char *ret = malloc(ret_len);

    ORDIE(ret != NULL, "Unable to create space for date");
    
    snprintf(ret, ret_len, "Date: %s, %02d %s %02d:%02d:%02d\r\n",
             days[t->tm_wday], t->tm_mday,
             months[t->tm_mon],
             t->tm_hour, t->tm_min, t->tm_sec);
    return ret;
}

char *maketo(const char *destination) {

    int to_len = strlen("To: ") + strlen(destination) + strlen(" \r\n") + 1;
    char *to = malloc(to_len);
    ORDIE(to != NULL, "Unable to allocate message for To line.");
    snprintf(to, to_len, "To: <%s> \r\n", destination);

    return to;
}

char *makemsgid() {
    uint64_t number = (((uint64_t)rand()) << 32) + rand();

    int ret_len = strlen("Message-ID: <") + digits(number) + strlen("@httpwatch>\r\n") + 1;

    char *ret = malloc(ret_len);
    ORDIE(to != NULL, "Unable to allocate message for MSGID line.");
    snprintf(ret, ret_len, "Message-ID: %ld@httpwatch\r\n", number);

    return ret;
}

char *payload[8];

size_t send_mail(void *ptr, size_t size, size_t nmemb, void *user) {
    struct mail *m = (struct mail*)user;

    char *data;

    if (size == 0 || nmemb == 0) {
        return 0;
    }

    data = payload[m->lines_sent];

    if (data) {
        size_t len = strlen(data);
        memcpy(ptr, data, len);
        m->lines_sent++;

        return len;
    }

    return 0;
}


void make_payload(char *destination, char *host) {
    char *date = makedate();
    char *to = maketo(destination);
    //const char *from = "From: ___(Notify)\r\n";
    char *msgid = makemsgid();
    const char *subject = "Subject: Host down!\r\n";
    const char *separator = "\r\n";
    size_t body_len = strlen("The host ")
        + strlen(host) + strlen("has gone down\r\n")
        + strlen("How do you want me to get this notifier to you?\r\n") + 1;
//    size_t body_len = strlen("If you got this, the notifier's pretty much done\r\nText me with how you want it sent to you.\r\n~ Danny\r\n") + 1;
    char *body = malloc(body_len);

    ORDIE(body != NULL, "Unable to allocate the message body");
//    snprintf(body, body_len, "If you got this, the notifier's pretty much done\r\nText me with how you want it sent to you.\r\n~ Danny\r\n");
snprintf(body, body_len, "The host %s has gone down\r\nHow do you want me to get this notifier to you?\r\n", host);


    payload[0] = date;
    payload[1] = to;
    payload[2] = (char*)from;
    payload[3] = msgid;
    payload[4] = (char*)subject;
    payload[5] = (char*)separator;
    payload[6] = body;
    payload[7] = NULL;

}
void email(char *destination, char *host) {
    make_payload(destination, host);

    CURL *mailer = curl_easy_init();
    struct curl_slist *to = NULL;
    struct mail m = {0};
#error "Make sure you define the needed information"
    //curl_easy_setopt(mailer, CURLOPT_USERNAME, "");
    //curl_easy_setopt(mailer, CURLOPT_PASSWORD, "");
    curl_easy_setopt(mailer, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
    curl_easy_setopt(mailer, CURLOPT_URL, "smtp://smtp.gmail.com:587");
    //curl_easy_setopt(mailer, CURLOPT_MAIL_FROM, "<>");
    to = curl_slist_append(to, destination);
    curl_easy_setopt(mailer, CURLOPT_MAIL_RCPT, to);

    curl_easy_setopt(mailer, CURLOPT_READFUNCTION, send_mail);
    curl_easy_setopt(mailer, CURLOPT_READDATA, &m);
    curl_easy_setopt(mailer, CURLOPT_UPLOAD, 1L);

    CURLcode result = curl_easy_perform(mailer);

    ORDIE(result == CURLE_OK , curl_easy_strerror(result));

    curl_slist_free_all(to);
    
    free(payload[0]);
    free(payload[1]);
    free(payload[3]);
    free(payload[6]);
    
    curl_easy_cleanup(mailer);
}

const int WARNTIME = 60;

void page_error(char *dest, char *host, bool sent_message) {
    if (!sent_message) {
        printf("Message not sent yet %ld\n", (time(NULL) - last_good_time)); 
        if ((time(NULL) - last_good_time) >= WARNTIME) {
            email(dest, host);
        }
    }
}
