#ifndef LINE_H
#define LINE_H

#include "point.h"
typedef struct line
{
    point start;
    point end;
} line;

line prompt_line(void);

void draw_line(SDL_Renderer *r, line line);
#endif
