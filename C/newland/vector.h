#ifndef VECTOR_H
#define VECTOR_H
struct vector
{
    void *contents;
    size_t next;
    size_t size;
};

struct vector new_vector()
{
    struct vector ret;
    ret.size = 64;
    ret.contents = malloc(sizeof(void*) * ret.size);
    ret.next = 0;
    return ret;
}

size_t vector_add(struct vector *v, void *content);
void vector_del(struct vector *v, size_t index);
void *vector_get(struct vector *v, size_t index);

#endif
