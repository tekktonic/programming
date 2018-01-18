#include "t_vect.h"

#include <stdlib.h>

static const size_t tv_default_size 64



const char *tv_errstrings[] = {
    "OK",
    "No memory",
    "No element"
};

struct t_vect t_vect_new(freefunc free, size_t size)
{
    struct t_vect ret;

    size = (size == -1) ? tv_default_size : size;
    
    ret.items = calloc(size, sizeof(void*));
    
    ret.free = free;
    
    ret.size = size;
    ret.taken = 0;
    
    return ret;
}

t_vect_err t_vect_ensure(struct t_vect *self, size_t capacity)
{
    if (self->size < capacity)
    {
        self->items = realloc(self->items, capacity * sizeof(*self->items));
        if (!self->items)
            return TV_ERR_NOMEM;

        self->size = capacity;
    }

    return TV_ERR_OK;
}

t_vect_err t_vect_add(struct t_vect *self, void *item)
{
    size_t offset = self->taken++;

    if (offset > self->size)
    {
        if (t_vect_ensure(self, self->size * 2) == TV_ERR_NOMEM)
        {
            return TV_ERR_NOMEM;
        }
    }
    self->items[offset] = item;

    return TV_ERR_OK;
}

t_vect_err t_vect_del(struct t_vect *self, size_t offset)
{
    if (offset >= self->taken)
        return TV_ERR_NOELM;

    for (size_t i = offset+1; i < self->taken; i++)
        self->items[i - 1] = self->items[i];
    self->items[self->taken--] = NULL;
    return TV_ERR_OK;
}

t_vect_err t_vect_delfree(struct t_vect *self, size_t offset)
{
    void *item;
    t_vect_err e;
    if ((e = t_vect_get(self, offset, &item)))
        return e;

    if ((e = t_vect_del(self, offset)))
        return e;

    if (self->free)
        self->free(item);

    return TV_ERR_OK;
}


t_vect_err t_vect_get(struct t_vect *self, size_t offset, void **out)
{
    if (offset >= self->taken)
        return TV_ERR_NOELM;

    *out = self->items[offset];
    return TV_ERR_OK;
}

t_vect_err t_vect_set(struct t_vect *self, size_t offset, void *item)
{ 
    if (offset >= self->taken)
        return TV_ERR_NOELM;

    self->items[offset] = item;
    return TV_ERR_OK;
}

t_vect_err t_vect_setfree(struct t_vect *self, size_t offset, void *item)
{
    if (self->taken >= offset)
        return TV_ERR_NOELM;

    self->free(self->items[offset]);
    self->items[offset] = item;
    return TV_ERR_OK;
}

void t_vect_free(struct t_vect **s)
{
    struct t_vect *self = *s;
    for (size_t i = 0; i < self->taken; i++)
    {
        self->free(self->items[i]);
    }

    free(self->items);
    free(*s);
    *s = NULL;
}

const char *t_vect_errstr(t_vect_err err)
{
    return tv_errstrings[-err];
}
