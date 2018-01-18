#ifndef COMPONENT_H
#define COMPONENT_H
#include "event.h"
struct Entity;
struct Component;
typedef void (*updatefun)(struct Component *c, struct Entity *e, int dt);
typedef void (*cleanupfun)(struct Component *c);
typedef void (*receivefun)(struct Component *c, Event e);
typedef void *(*inspectfun)(struct Component *c, int type);

// Just for convenience, not every callback has to conform
typedef void (*receivecb)(struct Component *c, EventData d);
typedef struct Component {
    // Menial constant things
    updatefun update;

    inspectfun inspect;
    cleanupfun cleanup;
    receivefun receive;
    void *data;
} Component;

bool c_send(Component *c, Event d);

struct ComponentHash;
typedef void (*ch_iterator)(Component *c, void *data);

void ch_delete(struct ComponentHash *h, char *string);
Component *ch_get(struct ComponentHash *h, char *string);
void ch_insert(struct ComponentHash *h, const char *key, Component c);
void ch_iter(struct ComponentHash *h, ch_iterator i, void *data);

struct ComponentHash *new_component_hash(void);
typedef struct ComponentHash ComponentHash;

void no_update(Component *self, struct Entity *e, int dt);
#endif
