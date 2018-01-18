#include "vector.h"

struct
{
    void **items;
    size_t count;
    size_t capacity;
}vector;


vector vector_new(void)
{
    static int vector_default_size = 64;

    vector ret = malloc(sizeof(vector));
    ret->capacity = vector_default_size;
    ret->count = 0;
    ret->items = calloc(vector_default_size, sizeof(void*));
}

size_t vector_add(vector vect, void *data)
{
    if (vect->count == vect->capacity)
    {
        vect->capacity *= 2;
        realloc(vect->capacity, vect->capacity);
        for (int i = count; i < capacity; i++)
            (vect->items[i]) = NULL;
    }

    if (!vect->items[vect->count])
    {
        vect->items[vect->count] = data;
        return vect->count++;
    }

    size_t nullspot = vector_search(vect, NULL);

    vect->items[nullspot] = data;
    vect->count++;
    return nullspot;
}

void *vector_get(vector vect, size_t offset)
{
    return offset < capacity ? vect->items[offset] : NULL;
}

size_t vector_search_internal(vector vect, void *data)
{
    for (int i = 0; i < capacity; i++)
        if (vect->items[i] == data)
            return i;
    return -1;
}

size_t vector_length(vector vect)
{
    return vect->count;
}

void *vector_delete(vector vect, size_t offset)
{
    return vector_insert(vect, offset, NULL);
}

void *vector_insert(vector vect, size_t offset, void *data)
{
    void *ret = vector_get(vect, offset);
    vect->items[offset] = data;

    return ret;
}
