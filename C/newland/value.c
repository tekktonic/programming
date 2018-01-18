#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "value.h"
#include "cons.h"

const char *type_strings[] = {"nil", "int", "double", "char", "cons", "ref", "func", "primfunc", "context",
                              "string", "unknown"};
struct value value_copy(const struct value *value)
{
    struct value ret = {.value = value->value, .t = value->t};
    return ret;
}

struct value new_int_value(int value)
{
    struct value ret = {.value.i = value, .t = VAL_INT};
    return ret;
}

struct value new_double_value(double value)
{
    struct value ret = {.value.d = value, .t = VAL_DOUBLE};
    return ret;
}

struct value new_char_value(char value)
{
    struct value ret = {.value.c = value, .t = VAL_CHAR};
    return ret;
}

struct value new_string_value(const char *value)
{
    struct value ret;
    printf("NEW STRING VALUE FOR %s", value);
    ret.value.s = malloc(strlen(value) * sizeof(char));
    snprintf(ret.value.s, strlen(value) * sizeof(char) + 1, "%s", value);
    ret.t = VAL_STRING;
    return ret;
}

struct value new_ctx_value(struct ctx *ctx)
{
    struct value ret;
    ret.value.ctx = ctx;
    ret.t = VAL_CTX;
    return ret;
}

struct value new_nil_value(void)
{
    struct value ret = {.t = VAL_NIL};
    return ret;
}

struct value new_cons_value(struct value car, struct cons *cdr)
{
    struct cons *ret_val = new_cons(car, cdr);
    struct value ret = {.value.cell = ret_val, .t = VAL_CONS};
    return ret;
}

struct value new_ref_value(struct value *value)
{
    struct value ret = {.value.ref = value, .t = VAL_REF};
    return ret;
}

/*struct value new_primfunc_value(struct value (*func)(struct value), struct value args)
{
    struct value ret = {.value.pf = {.func = func, .args = &args}, .t = VAL_PRIM};
    return ret;
    }*/


struct value new_unknown_value(void)
{
    struct value ret = {.value.ref = NULL, .t = VAL_UNKNOWN};
    return ret;
}

void print_value_debug(FILE *fp, const struct value *value)
{
    fprintf(fp, "value %p:\n\ttype: %s\n\tvalue: ", value, type_strings[value->t]);
    switch (value->t)
   { 
    case VAL_NIL:
        fprintf(fp, "nil");
        break;
    case VAL_INT:
        fprintf(fp, "%d", value->value.i);
        break;
    case VAL_DOUBLE:
        fprintf(fp, "%lf", value->value.d);
        break;
    case VAL_CHAR:
        fprintf(fp, "%c", value->value.c);
        break;
    case VAL_STRING:
        fprintf(fp, "%s", value->value.s);
        break;
    case VAL_CONS:
        print_cons(fp, value->value.cell);
        break;
    case VAL_REF:
        fprintf(fp, "%p", value->value.ref);
        break;
    default:
        fprintf(fp, "Invalid value passed.");
        break;
    }
    fprintf(fp, "\n");
}

void print_value(FILE *fp, const struct value *value)
{
    switch (value->t)
    {
    case VAL_NIL:
        fprintf(fp, "nil");
        break;
    case VAL_INT:
        fprintf(fp, "%d", value->value.i);
        break;
    case VAL_DOUBLE:
        fprintf(fp, "%lf", value->value.d);
        break;
    case VAL_CHAR:
        fprintf(fp, "%c", value->value.c);
        break;
    case VAL_STRING:
        fprintf(fp, "%s", value->value.s);
        break;
    case VAL_CONS:
        print_cons(fp, value->value.cell);
        break;
    case VAL_REF:
        fprintf(fp, "%p", value->value.ref);
        break;
    default:
        fprintf(fp, "Try passing a real value");
        break;
    }
}
