%module SDL2
%{
#include <SDL2/SDL.h>
%}

#define SDL_INIT_EVERYTHING 0x00000031

extern int SDL_Init(unsigned int flags);
