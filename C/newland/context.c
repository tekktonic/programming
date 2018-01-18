#include "context.h"
#include <string.h>
#include <stdlib.h>

struct value top_ctx_defined[] = {};

struct ctx top_ctx()
{
    struct ctx *ret = malloc(sizeof(*ret));
    ret->next_up = NULL;
    ret->i = 0;
    return ret;
}

void ctx_add
