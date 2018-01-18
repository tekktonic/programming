#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv;)
{
    if (argc < 2)
    {
	fprintf(stderr, "A binary to print the strings from is needed\n");
    }
    FILE *fp = fopen(argv[1], "r");

    if (!fp)
    {
	fprintf(stderr, "unable to open file: %s because %s", argv[1], strerror(errno));
    }

    
}
