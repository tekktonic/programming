#include "basic_collidec.h"

#include "../direction.h"
#include "../event.h"

static void update(Component *c, Entity *e, int dt) {
    Component *other_collide;
    
    Entity **entities = (Entity**)c->data;
    //This is a minor optimization; later on it may be worth
    //Optimizing more via a spatial hash, but for now deal with n^2
    
    for(int i = e->id; i < 256; i++) {
        if ((other_collide = ch_get(entities[i]->components, "collide"))) {
            // A component with collide *must* have a position
            Component *other_position = ch_get(entities[i]->components, "position");
        }
    }
}

Component new_basic_collidec(Entity **entities) {
    #error not yet implemented
    //return (Component){.cleanup = cleanup, .update = update, .receive = receive,
    //.data = entities};
}
