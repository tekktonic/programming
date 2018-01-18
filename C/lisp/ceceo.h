#ifndef STAS_H
#define STAS_H
#include <glib.h>
#include <glib/gprintf.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <gmp.h>


#include "types.h"
#include "object.h"
#include "num.h"
#include "string.h"
#include "lit.h"
#include "cons.h"
#include "parsehelp.h"

// this will only contain the things that actually need to be exposed, namely read and write

Object *read(FILE *fp);
void write(Object *obj);

gboolean IsA(Object *obj, Type type);
#endif
