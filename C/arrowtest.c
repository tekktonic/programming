#include <stdio.h>
#include <stdlib.h>

struct test{int foo;};

int main(void)
{
    struct test *t = malloc(sizeof(struct test));
    t→foo = 5;
}
