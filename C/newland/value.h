#ifndef VALUE_H
#define VALUE_H
#include <stdio.h>
#include "primitivefuncs.h"

enum value_type
{
    VAL_NIL,
    VAL_INT,
    VAL_DOUBLE,
    VAL_CHAR,
    VAL_CONS,
    VAL_REF,
    VAL_FUNC,
    VAL_PRIM,
    VAL_CTX,
    VAL_STRING,
    VAL_UNKNOWN // only used for parsing errors
};

struct value;
struct ctx;

union value_val
{
    int i;
    double d;
    char c;
    char *s;
    struct cons *cell;
    struct value *ref;
    struct ctx *ctx;
    struct primitivefunc *pf;
    void *func; // worry about that later
};

struct value
{
    enum value_type t;
    union value_val value;
};

struct value value_copy(const struct value *value);
struct value new_int_value(int value);
struct value new_double_value(double value);
struct value new_char_value(char value);
struct value new_string_value(const char *value);
struct value new_ctx_value(struct ctx *ctx);
struct value new_nil_value(void);
struct value new_unknown_value(void);
struct value new_cons_value(struct value car, struct cons *cdr);
struct value new_ref_value(struct value *value);
struct value new_primfunc_value(struct value (*func)(struct value), struct value args);

extern const char *type_strings[];


void print_value(FILE *fp,const struct value *value);
void print_value_debug(FILE *fp,const struct value *value);
#endif
