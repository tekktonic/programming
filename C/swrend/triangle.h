#ifndef T_TRIANGLE_H
#define T_TRIANGLE_H
#include <SDL2/SDL.h>

#include "point.h"

typedef struct triangle
{
    point p1;
    point p2;
    point p3;
}triangle;

triangle prompt_triangle(void);
void draw_triangle_unfilled(SDL_Renderer *r, triangle t);
void draw_triangle_filled(SDL_Renderer *r, triangle t);
void draw_triangle_filled_rect(SDL_Renderer *r, point tp1, point bp1, point tp2, point bp2);
#endif
