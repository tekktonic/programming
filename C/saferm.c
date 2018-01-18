#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define TIMES 5
int main(int argc, char **argv)
{
	for(int i = 1; i < (argc); ++i)
	{
	    for (int ii = 0; ii < TIMES; ++ii)
	    {
		struct stat st;
		int fd, urandom;
		char buf;
		if(0 == stat(argv[i], &st)) // 0 == form prevents a certain error
		{
			fd = open(argv[i], O_WRONLY);
			urandom = open("/dev/urandom", O_RDONLY); // it doesn't matter that the data is truly random, only that it's different
			for(int off = 0; off < st.st_size; ++off)
			{
				read(urandom, &buf, 1);
				write(fd, &buf, 1);
			}
			close(urandom);
			fsync(fd);
			close(fd);
		}
	    }
	unlink(argv[i]);

	}

	return 0;
}
