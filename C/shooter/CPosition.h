#ifndef CPOSITION_H
#define CPOSITION_H
#include <stdlib.h>
#include <assert.h>


typedef struct
{
    int x;
    int y;
}CPosition_s;

typedef CPosition_s *CPosition_t;

// just putting it in here because it really doesn't have much anyway

CPosition_t new_CPosition(int x, int y);

#endif
