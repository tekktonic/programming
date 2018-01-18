#include "CDrawable.h"


CDrawable_t new_CDrawable(const char *i, CPosition_t p)
{
    CDrawable_t ret = malloc(sizeof(CDrawable_s));
    assert(ret);
    assert(p);
    ret->p = p;
    ret->i = al_load_bitmap(i);
    assert(ret->i);
    return ret;
}

void CDrawable_Draw(CDrawable_t self)
{
    assert(self->i);
    al_draw_bitmap(self->i, self->p->x, self->p->y, 0);
}

void del_CDrawable(CDrawable_t self)
{
    al_destroy_bitmap(self->i);
    free(self);
}
