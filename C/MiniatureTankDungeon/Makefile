LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm
CFLAGS = -Wall -std=c11 -Wextra -g -O0

OBJS = topdown.o entity.o player.o sprite.o bullet.o event.o component.o components/drawc.o components/positionc.o 

topdown: $(OBJS)

clean:
	find . -name "*.o" -exec rm {} \;
	find . -name "*~" -exec rm {} \;
	find . -name "\#*\#" -exec rm {} \;
	find . -name ".\#*" -exec rm {} \;
	find . -name topdown -exec rm {} \;

