#include "Bullet.h"

float CalculateGoal(x, y, dx, dy)
{
    float ydiff = (dy > y) ? dy - y : y - dy;
    float xdiff = (dx > x) ? dx - x : x - dx;
    
    return ydiff / (xdiff + ydiff);
    // = ydiff / (xdiff + ydiff) * ((self->pos->y <= self->goal->y) ? Speed : -1 * Speed);
//    self->xSpeed = (1 - (ySpeed / Speed > 0) ? (self->ySpeed / Speed) : -1 * (self->ySpeed / Speed)) * ((self->pos->x <= self->goal->x) ? Speed : -1 * Speed;
}

Bullet_t new_Bullet(CPosition_t pos, CPosition_t goal, Owner owner)
{
    Bullet_t self = malloc(sizeof(Bullet_s));
    assert(self);
    self->pos = pos;
    self->owner = owner;


    self->goal = goal;
    self->ySpeed = (int)(CalculateGoal(self->pos->x, self->pos->y, self->goal->x, self->goal->y) * 
			 ((self->pos->y <= self->goal->y) ? 20 : -20));
    self->xSpeed = (int)((1 - ((self->ySpeed / 20.0 > 0) ? (self->ySpeed / 20.0) : -1 * (self->ySpeed / 20.0))) *
			 ((self->pos->x <= self->goal->x) ? 20 : -20));

    self->drawable = new_CDrawable("bullet.png", self->pos);
    return self;
}

void del_Bullet(Bullet_t self)
{
    Bullet_t *pself = &self;
    free(self->pos);
    del_CDrawable(self->drawable);
    free(self);
    *pself = NULL;
}

bool Bullet_Update(Bullet_t self) // return true if deleted
{
    assert(self);

    assert(self->pos);
    self->pos->x += self->xSpeed; //((self->goal->x - self->pos->x)) / 20;
    self->pos->y += self->ySpeed;
    if (self->pos->x > 640 || self->pos->x < 0 || self->pos->y > 480 || self->pos->y < 0)
    {
	del_Bullet(self);
	return true;
    }

    return false;
}

void Bullet_Draw(Bullet_t self)
{
    assert(self);
    assert(self->drawable);
    CDrawable_Draw(self->drawable);
}
