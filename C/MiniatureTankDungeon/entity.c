#include "entity.h"

#include <assert.h>

static int head = 0;
static int to_delete[256];
static int delete_head = 0;

void delete_clear() {
    for (int i = 0; i < 256; i++) {
        to_delete[i] = -1;
    }

    delete_head = 0;
}

void add_entity(Entity *e) {
    e->id = head;
    assert(head >= 0);
    entities[head++] = e;
    printf("%d\n", head);
}

// THIS LEAKS MEMORY
void delete_entity(int id) {
    to_delete[delete_head++] = id;
}

static int num_compare(const void *n1, const void *n2) {
    int i1 = *(int*)n1;
    int i2 = *(int*)n2;

    if (i1 < i2)
        return 1;
    else if (i1 > i2)
        return -1;
    else
        return 0;
}

void delete_commit(void) {
    if (delete_head) {
        qsort(to_delete, 256, sizeof(int), num_compare);
        for (int i = 0; i < 256 && to_delete[i] > -1; i++) {
            for (int ii = to_delete[i] + 1; ii < 256 && entities[ii - 1]; ii++) {
                if (ii == 256)
                    entities[ii - 1] = NULL;
                else
                    entities[ii - 1]  = entities[ii];
                if (entities[ii - 1])
                    entities[ii-1]->id = ii - 1;
            }
            assert(head >= 0);
        }
        head -= delete_head;
        delete_clear();
    }
}
