#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("/tmp/1", "wb");
    FILE *self = fopen("/proc/self/exe", "rb");

    int c = getc(self);

    while (!feof(self))
    {
	putc(c, fp);
	c = getc(self);
    }

    fclose(fp);
    fclose(self);
}
