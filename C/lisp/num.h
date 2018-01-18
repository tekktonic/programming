#ifndef STAS_NUM_H
#define STAS_NUM_H
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

#include "object.h"
#include "types.h"
#include "parsehelp.h"

Object *new_Num(gchar *str);
void del_Num(Object *num);

Object *ReadNum(FILE *fp);

void WriteNum(Object *num);

#endif
