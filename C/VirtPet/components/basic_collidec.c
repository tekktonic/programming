#include "basic_collidec.h"

#include <stdbool.h>

#include "positionc.h"
#include "../direction.h"
#include "../event.h"

typedef struct {
    collidecb cb;
}Collide;


static bool collide_check(SDL_Rect *first, SDL_Rect *other)
{
    // my x, my y, etc
    int mx = first->x;
    int my = first->y;
    int mx2 = first->x + first->w;
    int my2 = first->y + first->h;

    int ox = other->x;
    int oy = other->y;
    int ox2 = other->x + other->w;
    int oy2 = other->y + other->h;
            
    if ((mx <= ox2 && mx2 >= ox) || (ox <= mx2 && ox2 >= mx))
    {
        if ((my <= oy2 && my2 >= oy) || (oy <= my2 && oy2 >= my))
        {
            return true;
        }
    }
    return false;
}

static void update(Component *c, Entity *e, int dt) {
    Component *other_collide;
    
    Entity **entities = (Entity**)c->data;
    //This is a minor optimization; later on it may be worth
    //Optimizing more via a spatial hash, but for now deal with n^2
    
    for(int i = e->id; i < 256; i++) {
        if ((other_collide = ch_get(entities[i]->components, "collide"))) {
            // A component with collide *must* have a position
            Component *other_position = ch_get(entities[i]->components, "position");
            Component *position = ch_get(e, "position");
            SDL_Rect *me = (SDL_Rect*)position->inspect(position, POSITIONC_RECT);
            SDL_Rect *other = (SDL_Rect*)other_position->inspect(other_position,
                                                                 POSITIONC_RECT);
            if (collide_check(me, other)) {
                Collide *my_c = (Collide*)c->data;
                Collide *other_c = (Collide*)other_collide->data;
                if (my_c->cb)
                    my_c->cb(e, entities[i]);
                if (other_c->cb)
                    other_c->cb(entities[i], e);
            }
        }
    }
}

Component new_basic_collidec(Entity **entities) {
    #error not yet implemented
    //return (Component){.cleanup = cleanup, .update = update, .receive = receive,
    //.data = entities};
}
