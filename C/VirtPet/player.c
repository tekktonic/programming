#include "player.h"
#include "components/drawc.h"
#include "components/positionc.h"
#include "components/keyboardc.h"
#include "sprite.h"

void player_collide(Entity *self, Entity *other) {
    if (other->)
}
Entity *new_player(SDL_Renderer *r, int x, int y) {
    Entity p;
    p.render = new_drawc(r, SS_CHARACTER, 7, 10);

    p.components = new_component_hash();
    ch_insert(p.components, "position", new_positionc(x, y, 32, 32));
    ch_insert(p.components, "control", new_keyboardc(5));
    Entity *ret = malloc(sizeof(Entity));
    *ret = p;

    return ret;
}
