#include "pet.h"

#include "components/drawc.h"
#include "components/hungerc.h"
#include "components/positionc.h"
#include "components/followc.h"

Entity *new_pet(SDL_Renderer *r, int x, int y, enum PetTypes type, Component *owner) {
    Entity *ret = malloc(sizeof(Entity));
    ret->components = new_component_hash();
    ret->render = new_drawc(r, SS_CHARACTER, 4, 1);
    ret->components = new_component_hash();

    ch_insert(ret->components, "follow", new_followc(owner, 64, 5));
    ch_insert(ret->components, "position", new_positionc(x, y, 32, 32));
    ch_insert(ret->components, "hunger", new_hungerc(r));
    return ret;
}
