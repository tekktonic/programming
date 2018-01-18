#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(void)
{
    char tstr[9];
    time_t unxtime = time(NULL);
    struct tm *t = localtime(&unxtime);
    strftime(tstr, 9, "%H:%M:%S", t);
    printf("%s\n", tstr);
}
