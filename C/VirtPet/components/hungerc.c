#include "hungerc.h"


#include <SDL2/SDL.h>
#include <stdlib.h>

#include "../entity.h"

#include "drawc.h"
#include "healthc.h"
#include "positionc.h"

typedef struct {
    int satiation;
    double hungryChance;
    double healChance;
    Component draw;
    int ticks;

    Entity *dummy;
} Hunger;

static void cleanup(struct Component *self) {
    free(self->data);
}

static void update(struct Component *self, struct Entity *e, int dt) {
    Hunger *h = self->data;
    
    h->ticks += dt;
    
    if (h->ticks > 60) {
        double hungerRoll = ((double)random())/RAND_MAX;
        printf("Roll: %lf Req: %lf \n", hungerRoll, h->hungryChance);
        if (hungerRoll < h->hungryChance) {
            printf("Getting hungry");
            h->satiation--;
            h->hungryChance = 0.125;
        }
        else {
            h->hungryChance *= 2;
        }
        h->ticks = 0;

        if (h->satiation <= 0) {
            Component *health ;
            printf("Starving\n");
            
            
            if ((health = ch_get(e->components, "health"))) {
                Event e = {.t = HEALTHC_HARM, .d.i = 1};
                health->receive(health, e);
            }
            
        }
    

    
        if (h->satiation >= 5) {
            double healRoll = ((double)random())/RAND_MAX;

            if (healRoll < h->healChance) {
                Component *health ;
                printf("Healing\n");
                if ((health = ch_get(e->components, "health"))) {
                    Event e = {.t = HEALTHC_HEAL, .d.i = 1};
                    health->receive(health, e);
                }
            }
        }
    }

    if (h->satiation <= 0)
    {
        Component *iconpos = ch_get(h->dummy->components, "position");
        Component *position = ch_get(e->components, "position");
        SDL_Rect *myrect = (SDL_Rect*)position->inspect(position, POSITIONC_RECT);
        SDL_Rect pos = {.x = myrect->x, .y = myrect->y + myrect->h, .w = 16, .h = 16};
        Event e = {.t=POSITIONC_MOVE, .d.data=&pos} ;
        iconpos->receive(iconpos, e);
        h->draw.update(&h->draw, h->dummy, 1);
    }

    
    
};

Component new_hungerc(SDL_Renderer *r) {
    Component ret = {.cleanup = cleanup, .update = update};
    Hunger data = {.satiation = 0, .hungryChance = 0.125, .healChance = 0.01,
                   .draw = new_drawc(r, SS_THINGS, 6, 0), .dummy = malloc(sizeof(Entity))};
    data.dummy->components = new_component_hash();
    ch_insert(data.dummy->components, "position", new_positionc(0, 0, 16, 16));
    ret.data = malloc(sizeof(Hunger));
    *(Hunger*)ret.data = data;
    return ret;
}
