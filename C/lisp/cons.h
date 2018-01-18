#ifndef STAS_CONS_H
#define STAS_CONS_H
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

#include "object.h"
#include "types.h"
#include "parsehelp.h"
#include "ceceo.h"

Object *new_Cons(Object *car, Object *cdr);

Object *car(Object *cons);

Object *cdr(Object *cons);

Object *ReadCons(FILE *fp);
void WriteCons(Object *cons);

#define cadr(cons) car(cdr(cons))

void SetCar(Object *cons, Object *value);
void SetCdr(Object *cons, Object *value);
#endif
