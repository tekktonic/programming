#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>
typedef enum {
    SS_BASIC,
    SS_CHARACTER,
    SS_DEAD,
    SS_THINGS
} Spritesheets;

void draw_sprite(SDL_Renderer *r, Spritesheets sheet, int row, int column,
                 SDL_Rect *where);

void init_spritesheets(SDL_Renderer *r);
#endif
