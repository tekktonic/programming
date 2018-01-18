#include "healthc.h"

#include <stdlib.h>

typedef struct {
    int health;
}Health;

static void cleanup(Component *self) {
    free(self->data);
}

static void receive(Component *c, Event e) {
    switch(e.t) {
    case HEALTHC_HEAL:
        ((Health*)c->data)->health += e.d.i;
    case HEALTHC_HARM:
        ((Health*)c->data)->health -= e.d.i;
    default:
        break;
    }
}

static void *inspect(Component *self, int type) {
    switch (type) {
    case HEALTHC_HEALTH:
        return &((Health*)self->data)->health;
    }
}
Component new_healthc(int health) {
    Component ret = {.cleanup = cleanup, .update = no_update, .receive = receive};
    Health data = {.health = health};
    ret.data = malloc(sizeof(Health));
    *(Health*)ret.data = data;
    return ret;
}

