#ifndef CSTEPPER_H
#define CSTEPPER_H
#include <stdio.h>
#include "Tuple.h"
#include "CPosition.h"

typedef struct
{
    float xSpeed, ySpeed;
    CPosition_t pos;
    CPosition_t goal;
}CStepper_s;

typedef CStepper_s *CStepper_t;

void CStepper_Update(float x, float y, float dx, float dy, int Speed)
{
    float ydiff = (dy > y) ? dy - y : y - dy;
    float xdiff = (dx > x) ? dx - x : x - dx;

    self->ySpeed = ydiff / (xdiff + ydiff) * ((self->pos->y <= self->goal->y) ? Speed : -1 * Speed);
    self->xSpeed = (1 - (ySpeed / Speed > 0) ? (self->ySpeed / Speed) : -1 * (self->ySpeed / Speed)) * ((self->pos->x <= self->goal->x) ? Speed : -1 * Speed;
}

#endif
