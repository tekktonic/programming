#ifndef SPRITE_H
#define SPRITE_H
#include <SDL2/SDL.h>

typedef struct 
{
	int start, end;
}Frames;

typedef struct
{
	SDL_Texture **images;
	SDL_Rect pos;
	Frames frames;
}Animation;
#endif
