#ifndef BULLET_H
#define BULLET_H
#include "CPosition.h"
#include "CDrawable.h"
#include "Direction.h"
#include "Owner.h"
#include <stdbool.h>

typedef struct
{
    CPosition_t pos;
    CDrawable_t drawable;
    float updateSpeed;
    CPosition_t goal;
    int xSpeed, ySpeed;
    Owner owner;
}Bullet_s;

typedef Bullet_s *Bullet_t;

Bullet_t new_Bullet(CPosition_t pos, CPosition_t goal, Owner owner);

void del_Bullet(Bullet_t self);


bool Bullet_Update(Bullet_t self);

void Bullet_Draw(Bullet_t self);



#endif
