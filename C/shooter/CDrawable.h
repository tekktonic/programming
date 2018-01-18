#ifndef CDRAWABLE_H
#define CDRAWABLE_H
#include <allegro.h>
#include "CPosition.h"
#include <assert.h>
typedef struct
{
    ALLEGRO_BITMAP *i;
    CPosition_t p;
}CDrawable_s;

typedef CDrawable_s *CDrawable_t;

CDrawable_t new_CDrawable(const char *i, CPosition_t p);
void CDrawable_Draw(CDrawable_t self);
void del_CDrawable(CDrawable_t self);
#endif
