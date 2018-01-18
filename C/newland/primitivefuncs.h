#ifndef PRIMITIVEFUNC_H
#define PRIMITIVEFUNC_H
struct primitivefunc
{
    struct value (*func)(struct value);
    struct value *args;
};

#endif
