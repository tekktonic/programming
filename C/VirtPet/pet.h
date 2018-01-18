#ifndef PET_H
#define PET_H
#include "entity.h"

enum PetTypes {
    PET_DEFAULT
};
    
Entity *new_pet(SDL_Renderer *r, int x, int y, enum PetTypes type, Component *owner);
#endif
