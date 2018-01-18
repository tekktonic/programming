#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

static const char *id = "tekk";
int main(int argc, char **argv)
{
    assert(argc > 1);
    // assume we have enough space to hold the fs
    int fd = open(argv[1], O_RDWR);
    char *metadata = calloc(68, sizeof(*metadata));

    write(fd, id, 5);
    write(fd, (uint32_t)0, 4); // free bitmap
    for (int i = 0; i < 32; ++i) // create the metadata section. 256 files possible
	write(fd, metadata, 68);

    close(fd);
    /* no need to set the fs size */
}
