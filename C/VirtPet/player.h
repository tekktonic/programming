#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include "entity.h"

Entity *new_player(SDL_Renderer *r, int x, int y);
#endif
