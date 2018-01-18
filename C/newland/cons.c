#include "cons.h"

#include <stdlib.h>

struct cons *new_cons(struct value car, struct cons *cdr)
{
    struct cons *ret = malloc(sizeof(struct cons));
    ret->car = car;
    ret->cdr = cdr;
    return ret;
}

void print_cons(FILE *fp, const struct cons *c)
{
    fprintf(fp, "(");
    print_value(fp, &(c->car));
 
    if (c->cdr)
    {
        fprintf(fp, " . ");
        print_cons(fp, c->cdr);
    }

    fprintf(fp, ")");
}
