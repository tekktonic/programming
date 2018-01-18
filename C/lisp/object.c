#include "object.h"

Object *new_Object()
{
    Object *ret = malloc(sizeof(Object));
    ret->mutable = FALSE;

    if (!ret)
    {
	fprintf(stderr, "Unable to allocate new object!\n");
	exit(1);
    }

    return ret;
}

