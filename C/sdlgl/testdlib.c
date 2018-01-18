#include <stdio.h>
#include "dlib.h"

int main(void)
{
    char *file = slurp("sdlgl.c");
    printf("%s\n", file);
}
