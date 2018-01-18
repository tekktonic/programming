#include <stdbool.h>

#include <SDL2/SDL.h>

#include "bullet.h"
#include "component.h"
#include "direction.h"
#include "entity.h"
#include "keyboard.h"
#include "sprite.h"
#include "team.h"

typedef struct {
    double xSpeed;
    double ySpeed;
    double timeout;
    Direction d;
    int health;
    SDL_Rect position;
    double invincible;
    SDL_Renderer *r;
} Player;


static void render(Component *self, SDL_Renderer *r) {
    Player *p = (Player*)self->data;

    static bool blinky = false;
    static int time = 0;
    {
        SDL_Rect heart = {.x = 20, .y = 20};
        for (int i = 0; i < p->health; i++) {
            draw_sprite(r, SS_THINGS, 6, 1, &heart);
            heart.x += 36;
        }
    }

    
    if (!p->invincible) {
        blinky = false;
        draw_sprite(r, SS_CHARACTER, 4+p->d, 1, &p->position);
    }
    else if (!blinky) {
        draw_sprite(r, SS_CHARACTER, 4+p->d, 1, &p->position);
        time = (time == 0 ? blinky = !blinky, 4 : time-1);
    }
    else
    {
        time = (time == 0 ? blinky = !blinky, 4 : time-1);
    }


}

static void update(Component *self, Entity *e, int dt) {
    Player *p = (Player*)self->data;
    if (keyboard[SDL_SCANCODE_RIGHT])
        p->xSpeed = 6;
    if (keyboard[SDL_SCANCODE_LEFT])
        p->xSpeed = -6;
    if (!keyboard[SDL_SCANCODE_RIGHT] && !keyboard[SDL_SCANCODE_LEFT])
        p->xSpeed = 0;
    
    if (keyboard[SDL_SCANCODE_DOWN])
        p->ySpeed = 6;
    if (keyboard[SDL_SCANCODE_UP])
        p->ySpeed = -6;
    if (!keyboard[SDL_SCANCODE_DOWN] && !keyboard[SDL_SCANCODE_UP])
        p->ySpeed = 0;
    if (keyboard[SDL_SCANCODE_H] && !p->invincible) {
        p->health--;
        p->invincible = 60.;
    }
    else
        p->invincible = p->invincible == 0 ? p->invincible : p->invincible-1;

    Entity *bullet= NULL;
    if (keyboard[SDL_SCANCODE_W]) {
        bullet= new_bullet(p->r, p->position.x, p->position.y, p->xSpeed,
                                 p->ySpeed, DIR_N, TEAM_PLAYER);
    }
    else if (keyboard[SDL_SCANCODE_D]) {
        bullet= new_bullet(p->r, p->position.x, p->position.y, p->xSpeed,
                                 p->ySpeed, DIR_E, TEAM_PLAYER);        
    }
    else if (keyboard[SDL_SCANCODE_S]) {
        bullet= new_bullet(p->r, p->position.x, p->position.y, p->xSpeed,
                                 p->ySpeed, DIR_S, TEAM_PLAYER);
    }
    else if (keyboard[SDL_SCANCODE_A]) {
        bullet= new_bullet(p->r, p->position.x, p->position.y, p->xSpeed,
                                 p->ySpeed, DIR_W, TEAM_PLAYER);
    }

    if (bullet)
        add_entity(bullet);
    
    p->position.x += p->xSpeed;
    p->position.y += p->ySpeed;

    render(self, p->r);
}

static void cleanup(Component *self) {
    free((Player*)self->data);
}

Entity *new_player(SDL_Renderer *r, int x, int y) {
    Entity *ret = malloc(sizeof(Entity));

    ret->render = malloc(sizeof(Component));
    *ret->render = (Component){.update = update, .cleanup = cleanup};

    ret->components = new_component_hash();
/*    ret->update = update;
    ret->render = render;
    ret->cleanup = cleanup;
    ret->position = (SDL_Rect){.x = x, .y = y};
    ret->health = 8;*/

    ret->render->data = malloc(sizeof(Player));
    Player *p = (Player*)ret->render->data;
    p->xSpeed = p->ySpeed = 0;
    p->timeout = 0.;
    p->d = DIR_S;
    p->invincible = 0;
    p->position = (SDL_Rect){.x = x, .y = y};
    p->health = 8;
    p->r = r;
    
    return ret;
}
