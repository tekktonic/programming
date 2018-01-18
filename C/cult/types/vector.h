#ifndef VECTOR_H
#define VECTOR_H

struct vector;

typedef struct vector *vector;

vector vector_new(void);

// Return the position in the vector
size_t vector_add(vector vect, void *data);

void *vector_get(vector vect, size_t offset);

size_t vector_search(vector vect, void *data);

size_t vector_itemCount(vector vect);
// Provide the pointers to old data back so that they can be freed.
void *vector_delete(vector vect, size_t offset);
void *vector_insert(vector vect, size_t offset, void *data);
#endif
