#include <stdio.h>

int main(void)
{
    FILE *fp = fopen(strncat(, "wb");
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
