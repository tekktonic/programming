#include <stdbool.h>

#include <SDL2/SDL.h>

#include "entity.h"
#include "direction.h"
#include "keyboard.h"
#include "sprite.h"
#include "team.h"

#include "components/drawc.h"
#include "components/positionc.h"

typedef struct {
    double xSpeed;
    double ySpeed;
    Team t;
    Direction d;
    int health;
} Bullet;


/*static void render(Component *self, SDL_Renderer *r) {
    draw_sprite(r, SS_CHARACTER, 6, 11, &((Bullet*)self->data)->position);
    }*/

static void update(Component *self, Entity *e, int dt) {
    Bullet *p = (Bullet*)self->data;
    SDL_Rect mov = {.x = p->xSpeed, .y = p->ySpeed};
    Component *position = ch_get(e->components, "position");
    c_send(position, (Event){.t=POSITIONC_MOVE_REL, .d = &mov});
//    render(self, p->r);
}

static void cleanup(Component *self) {
    free((Bullet*)self->data);
}

Entity *new_bullet(SDL_Renderer *r, int x, int y, double xSpeed, double ySpeed,
                   Direction direction, Team team) {
    Entity *ret = malloc(sizeof(Entity));
    ret->render = malloc(sizeof(Component));
    *ret->render = new_drawc(r, SS_CHARACTER, 6, 11);

    ret->components = new_component_hash();
    ch_insert(ret->components, "bullet",
              (Component){.update = update, .cleanup = cleanup});

    ch_insert(ret->components, "position", new_positionc(x, y, 16, 16));

    Component *self = ch_get(ret->components, "bullet");
    self->data = malloc(sizeof(Bullet));
    Bullet *b = (Bullet*)self->data;

    b->xSpeed = xSpeed;
    b->ySpeed = ySpeed;
    b->health = 1;
    
    switch (direction) {
    case DIR_S:
        b->ySpeed += 16.;
        break;
    case DIR_W:
        b->xSpeed -= 16.;
        break;
    case DIR_E:
        b->xSpeed += 16.;
        break;
    case DIR_N:
        b->ySpeed -= 16.;
        break;
    }
    
    b->d = direction;
    b->t = team;
    return ret;
}
