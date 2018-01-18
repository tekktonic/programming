#ifndef CONTEXT_H
#define CONTEXT_H
#include "value.h"
struct ctx
{
    char *key[256];
    struct value *values[256];
    int i;
    // context is like a dynamically constructed stack, if what we want isn't in the stack just keep going up
    // arguments are only slightly special in that they're copied rather than just thrown into the context
    struct ctx *next_up;
};

struct ctx *top_ctx();
struct ctx *create_ctx(struct ctx *parent);

void ctx_add(struct ctx *ctx, const char *name, struct value *value);
struct value ctx_add(struct ctx *ctx, const char *name, struct value *value);
#endif
