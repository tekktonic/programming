CFLAGS=-Wall -Wextra -Wpedantic -std=c11 `pkg-config --cflags jansson sdl2 SDL2_image` -Iinc -g

LDFLAGS=`pkg-config --libs jansson sdl2 SDL2_image` -ldtype
OBJS=src/main.o src/resourcemanager.o src/room.o src/sample.o src/window.o src/sprite.o
all: kitty
kitty: $(OBJS)

	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o kitty

clean:
	if [ -e kitty ]; then rm kitty; fi

	find . -name "*~" -or -name "*.o" -exec rm {} \;
