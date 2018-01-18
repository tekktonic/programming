#ifndef ENTITY_H
#define ENTITY_H
#include <ncurses.h>
#include "player.h"

struct Entity_s
{
    char vis;
    unsigned long attrs[8];
    int position[2];
    void *data;
};

typedef struct Entity_s *Entity;

void print_entity(Entity entity)
{
    unsigned long *attr = entity->attrs;
    smove(entity->position[0], entity->position[1]);
    for (;*attr != 0; attron(*attr), ++attr);
    printw("%c", entity->vis);

    attr = entity->attrs;
    for (;*attr != 0; attroff(*attr), ++attr);
}
#endif
