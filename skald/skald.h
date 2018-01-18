#ifndef SKALD_H
#include <stdbool.h>
#include <time.h>
#define ORDIE(v, message) do{if (!(v)) {fprintf(stderr, "%s\n", message);}}while(0)

extern time_t last_good_time;
void page_error(char *dest, char *host, bool sent_message);

int max(int a, int b);
#endif
