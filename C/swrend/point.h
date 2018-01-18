#ifndef POINT_H
#define POINT_H
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>


typedef struct point
{
    int x;
    int y;
} point;

void draw_point(SDL_Renderer *r, point p);

point prompt_point(void);

int point_distance(point p1, point p2);

point point_mid(point p1, point p2);
#endif
