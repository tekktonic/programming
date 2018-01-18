#include <sys/types.h>
#include <fcntl.h>


int main(int argc, char **argv) {
	int fd = open(argv[1], O_RDONLY);
	char buf[256];
	int gotten;
	while ((gotten = read(fd, buf, 256))) {
		write(1, buf, gotten);
	}
}
