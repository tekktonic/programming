#include "stringutil.h"
#include <stdio.h>

int main(void)
{
    SplitString answer = malloc(sizeof(*answer));

    strsplit("a test", ' ', answer);

    printf("%s, %s", answer->string, answer->next->string);
}
