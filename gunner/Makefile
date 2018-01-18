OBJS = gunner.o

CFLAGS = -Wall -Wextra -std=c99 `curl-config --cflags`
LDFLAGS = `curl-config --libs`

gunner: $(OBJS)

clean:
	rm *.o *~ gunner
