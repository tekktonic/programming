#ifndef WINDOW_H
#define WINDOW_H
#include "sprite.h"
typedef struct {
	SDL_Window *window; // type punning <3
	int ow, oh;
} Window;

Window_draw(struct Window *window, Sprite spr);

