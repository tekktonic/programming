#ifndef TEXTINPUT_H
#define TEXTINPUT_H
#include <SDL.h>

#include "globals.h"

int textinput_int(SDL_Renderer *r);
char *textinput_string(SDL_Renderer *target);
#endif
