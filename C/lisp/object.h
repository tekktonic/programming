#ifndef STAS_OBJECT_H
#define STAS_OBJECT_H

#include <glib.h>
#include <gmp.h>

#include <stdlib.h>
#include <stdio.h>

#include "types.h"

typedef struct Object
{
    Type type;
    gboolean mutable;
    union
    {
	struct {
	    mpf_t num;
	}Num;

	struct {
	    GString *string;
	}String;

	struct {
	    GString *literal;
	}Literal;

	struct {
	    gchar truthiness; // "bool" is already a type
	    // t for true, f for false. simplifies printing *and* doesn't use any more memory
	}Bool;

	struct Cons
	{
	    struct Object *car;
	    struct Object *cdr;
	}Cons;

    }data;
}Object;


Object *t;
Object *f;
Object *nil;

Object *new_Object();

#endif
