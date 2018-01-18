/**
 * battmon, a simple power manager.
 */

#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>

#include "config.h"

#ifdef __linux__
#include "battmon_linux.h"
#else
#error "Only linux is supported at the moment"
#endif

enum acstat
{
    PLUGGED,
    UNPLUGGED
};

enum barpos
{
    TOP,
    BOTTOM
};

struct battery
{
    short percentage;
    enum acstat acstat;
};



Display *d;
Window *w;
GC *bardraw;

void init(void)
{
    XSetWindowAttributes attrs = {.override_ridirect = True};
    int scr, w, h;
    d = XOpenDisplay(NULL);

    if (!d)
    {
        fprintf(stderr, "Unable to open display\n");
        exit(1);
    }

    
}
