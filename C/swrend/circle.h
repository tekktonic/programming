#ifndef CIRCLE_H
#define CIRCLE_H
#include <SDL2/SDL.h>
#include "point.h"
typedef struct circle
{
    point center;
    int radius;
}circle;

circle prompt_circle(void);
void draw_circle(SDL_Renderer *r, circle c);

#endif
