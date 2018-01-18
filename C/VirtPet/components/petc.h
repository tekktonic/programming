#ifndef PETC_H
#define PETC_H
#include "../component.h"
#include "../entity.h"

typedef enum {
    PETC_PET
}PetCInspects;
Component new_petc(Entity *pet);
#endif
