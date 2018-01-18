#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>

enum WindowType {
    WT_FLOATING,
    WT_TILED,
    WT_FIXED
};

enum {EA_NETSUPPORTED, EA_NETNAME, EA_NETLAST};

enum {AT_WMPROTOCOLS, AT_WMDELETE, AT_WMSTATE, AT_WMLAST};

struct Client {
    char name[256];
    int x, y, w, h;

    Window xwin;
};

struct Key {
    KeySym sym;
};

struct Layout {
    const char *sym;
    void (*arrange)(Client *windows);
};

void mainloop(Display *dpy)
{
    XEvent e;
    int xfd;
    
    XSync(dpy, False);
    xfd = connectionNumber(dpy);
}
