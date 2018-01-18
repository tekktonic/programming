#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include "tonic.h"

// I think this is safe? maybe not.
typedef struct
{
    SDL_Texture *tex;
    Rect rect;
} Sprite_s;

typedef Sprite_s *Sprite;

void Sprite_kill(Sprite self);
#endif
