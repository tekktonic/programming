#ifndef CONS_H
#define CONS_H
#include <stdio.h>

#include "value.h"

struct cons
{
    struct value car;
    struct cons *cdr;
};

struct cons *new_cons(struct value car, struct cons *cdr);
void print_cons(FILE *fp, const struct cons *c); // performance

#endif
