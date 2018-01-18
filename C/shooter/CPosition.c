#include "CPosition.h"


CPosition_t new_CPosition(int x, int y)
{
    CPosition_t ret = malloc(sizeof(CPosition_s));
    assert(ret);
    ret->x = x;
    ret->y = y;
    return ret;
}
