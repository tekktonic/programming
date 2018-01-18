#ifndef T_VECT_H
#define T_VECT_H
#include "t_global.h"
#include <stddef.h>

typedef enum t_err
{
    T_ERR_OK = 0,
    T_ERR_NOMEM = -1,
    T_ERR_NOELM = -2,
} t_err;

struct t_vect
{
    void **items;
    size_t size;
    size_t taken;
    // For when the vect is freed
    freefunc free;
};

struct t_vect *t_vect_new(freefunc free);
t_vect_err t_vect_ensure(struct t_vect *self, size_t capacity);

t_vect_err t_vect_add(struct t_vect *self, void *item);
t_vect_err t_vect_del(struct t_vect *self, size_t offset);
t_vect_err t_vect_delfree(struct t_vect *self, size_t offset);

t_vect_err t_vect_get(struct t_vect *self, size_t offset, void **out);
t_vect_err t_vect_set(struct t_vect *self, size_t offset, void *item);
t_vect_err t_vect_setfree(struct t_vect *self, size_t offset, void *item);

void t_vect_free(struct t_vect **s);

const char *t_vect_errstr(t_vect_err err);
#endif
