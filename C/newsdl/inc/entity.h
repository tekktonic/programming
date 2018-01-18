#ifndef ENTITY_H
#define ENTITY_H
#include <dtype.h>
#include <stdarg.h>
#include <jansson.h>
#include "sprite.h"
// this has a struct public because it's an interface.
struct Entity_s
{
    Sprite (*draw)(struct Entity_s *self);
    void (*update)(struct Entity_s *self);
    void (*react)(struct Entity_s *self);
    void (*kill)(struct Entity_s *self);
    bool physical;
    char *type;
    Rect *rect;
    void *data;
};

typedef struct Entity_s *Entity;

FHash constructors;
void EnableEntities(const char *name, Entity *constructor(json_t *args), ...);
#endif
