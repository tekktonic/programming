#ifndef BASIC_COLLIDEC
#define BASIC_COLLIDEC
#include "../entity.h"
#include "../component.h"

typedef enum {
    COLLIDE_BASIC,
    COLLIDE_TEAM
} CollideCEvents;

Component new_basic_collidec(Entity **entities);
#endif
