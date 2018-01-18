#ifndef PLAYER_H
#define PLAYER_H
#include "CPosition.h"
#include "CDrawable.h"
#include "Bullet.h"
typedef struct
{
    CPosition_t pos;
    CDrawable_t drawable;

    Bullet_t bullets[BULLETARRAY_SIZE];
