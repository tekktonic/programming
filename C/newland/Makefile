
KEYBOARD = 0
CONTROLLER = 1

INPUT ?= $(KEYBOARD)

CFLAGS = -Wall -Wextra -std=c11 -g 
LDFLAGS = -lreadline -lncurses
BINARY = newland

OBJS = newland.o cons.o value.o parselib.o
all: newland clean
newland: $(OBJS)

clean:
	find . -name "*.o" -exec rm {} \;
	find . -name "*~" -exec rm {} \;
	find . -name "\#*\#" -exec rm {} \;
	find . -name ".\#*" -exec rm {} \;

extra-clean:
	find . -name $(BINARY) -exec rm {} \;
