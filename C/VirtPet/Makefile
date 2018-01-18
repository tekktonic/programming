LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm
CFLAGS = -Wall -std=c11 -Wextra -g -O0

OBJS = main.o util.o entity.o player.o pet.o sprite.o event.o component.o components/drawc.o components/positionc.o components/keyboardc.o components/followc.o components/hungerc.o components/petc.h

VirtPet: $(OBJS)
	gcc $(OBJS) -o VirtPet $(LDFLAGS) $(CFLAGS)
clean:
	find . -name "*.o" -exec rm {} \;
	find . -name "*~" -exec rm {} \;
	find . -name "\#*\#" -exec rm {} \;
	find . -name ".\#*" -exec rm {} \;
	find . -name VirtPet -exec rm {} \;

