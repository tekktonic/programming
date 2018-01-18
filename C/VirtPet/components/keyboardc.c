#include "keyboardc.h"
#include "../entity.h"
#include <SDL2/SDL.h>

#include "positionc.h"

static void update(Component *c, Entity *ent, int dt) {
    const Uint8 *keyboard;
    int speed = (int)c->data;
    
    keyboard = SDL_GetKeyboardState(NULL);
    Component *position = ch_get(ent->components, "position");
    Event e = {.t = POSITIONC_MOVE_REL};
    SDL_Rect movement;
    if (keyboard[SDL_SCANCODE_UP]) {
        movement = (SDL_Rect){.y = -speed};
        e.d.data = &movement;
        position->receive(position, e);
    }
    else if(keyboard[SDL_SCANCODE_DOWN]) {
        
        movement = (SDL_Rect){.y = speed};
        e.d.data = &movement;
        position->receive(position, e);
    }

    if (keyboard[SDL_SCANCODE_LEFT]) {
        
        movement = (SDL_Rect){.x = -speed};
        e.d.data = &movement;
        position->receive(position, e);
    }
    else if(keyboard[SDL_SCANCODE_RIGHT]) {
        
        movement = (SDL_Rect){.x = speed};
        e.d.data = &movement;
        position->receive(position, e);
    }
}

Component new_keyboardc(int speed) {
    Component ret = {.update = update};
    ret.data = (void*)speed;

    return ret;
}
