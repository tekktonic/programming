#include "vector.h"

size_t vector_add(struct vector *v, void *content)
{
    if (v->size == v->next)
    {
        v->size *= 2;
        v->contents = realloc(v->contents, v->size);
    }

    v->contents[v->next] = content;
    return v->next++;
}

size_t vector_del(struct vector *v, size_t index)
{
    
}
