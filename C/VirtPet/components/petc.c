#include "petc.h"

void *inspect(Component *self, int type) {
    return self->data;
}

Component new_petc(Entity *pet) {
    Component ret = {.update=no_update, .data = pet, .inspect=inspect};
    return ret;
}
