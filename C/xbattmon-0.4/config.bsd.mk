PREFIX = /usr/local
MANPREFIX = $(PREFIX)/man

CPPFLAGS = -DPATH_APM='"/dev/apm"'
CFLAGS = -I/usr/X11R6/include
LDFLAGS = -L/usr/X11R6/lib
LDLIBS = -lX11
