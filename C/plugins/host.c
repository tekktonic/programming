#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    void *lib = dlopen(argv[1], RTLD_LAZY); /* only pull in functions when called */

    void (*SayHi)() = dlsym(lib, "SayHi");

    if (!lib || !SayHi)
	printf("%s\n", dlerror());
    SayHi();
    return 0;
}
