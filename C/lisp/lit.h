#ifndef STAS_LIT_H
#define STAS_LIT_H
#include <glib.h>
#include <glib/gprintf.h>

#include <stdlib.h>
#include <stdio.h>

#include "object.h"
#include "types.h"
#include "parsehelp.h"

Object *new_Literal(GString *sym);
Object *ReadLiteral(FILE *fp);
void del_Literal(Object *obj);
void WriteLiteral(Object *num);

#endif
