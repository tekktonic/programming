#ifndef POSITIONC_H
#define POSITIONC_H

#include "../component.h"
#include "../entity.h"

typedef enum {
    POSITIONC_MOVE,
    POSITIONC_MOVE_REL
} PositionCEvents;

typedef enum {
    POSITIONC_RECT,
    POSITIONC_CENTER,
} PositionCInspects;

typedef void (*collidecb)(Entity *self, Entity *other);

Component new_positionc(int x, int y, int w, int h);
#endif
