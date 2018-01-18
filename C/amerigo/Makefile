CFLAGS = -Wall -Wextra -std=c11 -g 
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -ljansson

UNAME_S = $(shell uname -s)

ifeq (${UNAME_S}, OpenBSD)
	CC=egcc
	CFLAGS += -I/usr/local/include/SDL2
	LDFLAGS += -L/usr/X11R6/lib/
endif

ifeq (${PROFILE}, yes)
	CFLAGS += -pg

	LDFLAGS += -pg
endif

LDFLAGS += -lm -lpthread
CFLAGS += -D_REENTRANT -I/usr/include/SDL2
BINARY = amerigo

OBJS = amerigo.o tile.o textinput.o

amerigo: $(OBJS)

clean:
	find . -name "*.o" -exec rm {} \;
	find . -name "*~" -exec rm {} \;
	find . -name "\#*\#" -exec rm {} \;
	find . -name ".\#*" -exec rm {} \;
	find . -name $(BINARY) -exec rm {} \;
