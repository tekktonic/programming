#ifndef STAS_STRING_H
#define STAS_STRING_H
#include <glib.h>
#include <glib/gprintf.h>

#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "object.h"
#include "parsehelp.h"

Object *new_String(GString *str);
void del_String(Object *string);

Object *ReadString(FILE *fp);

void WriteString(Object *str);
#endif
