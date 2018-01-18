OBJS = skald.o

BINARIES = skaldhttp skaldhttps
CFLAGS = -Wall -Wextra -std=c99 `curl-config --cflags` -g
LDFLAGS = `curl-config --libs`

all: $(BINARIES)
skaldhttp: skaldhttp.o skald.o
skaldhttps: skaldhttps.o skald.o

clean:
	rm *.o *~ $(BINARIES)
