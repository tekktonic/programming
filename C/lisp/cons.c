#include "cons.h"

Object *new_Cons(Object *car, Object *cdr)
{
    Object *ret = new_Object();

    ret->type = CONS;
    ret->data.Cons.car = car;
    ret->data.Cons.cdr = cdr;

    return ret;
}

Object *car(Object *cons)
{
    return cons->data.Cons.car;
}

Object *cdr(Object *cons)
{
    return cons->data.Cons.cdr;
}

void SetCar(Object *cons, Object *val)
{
    cons->data.Cons.car = val;
}

void SetCdr(Object *cons, Object *val)
{
    cons->data.Cons.cdr = val;
}

Object *ReadCons(FILE *fp)
{
    Object *car_o;
    Object *cdr_o;
    gchar c;
    chomp(fp);

    c = getc(fp);
    if (c == ')')
	return nil;
    ungetc(c, fp);

    car_o = read(fp);
    chomp(fp);

    c = getc(fp);
    if (c == '.') // improper list/pair
    {
	if (!IsA_Delimiter((c = peek(fp))))
	{
	    fprintf(stderr, ". not followed by delimiter\n");
	    exit(1);
	}
	cdr_o = read(fp);
	chomp(fp);
	c = getc(fp);
	if (c != ')')
	{
	    fprintf(stderr, "No closing paren in pair. did you mean to use a list?\n");
	    exit(1);
	}
	return new_Cons(car_o, cdr_o);
    }
    else
    {
	ungetc(c, fp);
	cdr_o = ReadCons(fp);
//	getc(fp);
	return new_Cons(car_o, cdr_o);
    }
}

void WriteCons(Object *cons)
{
    Object *car_o = car(cons);
    Object *cdr_o = cdr(cons);

    write(car_o);
    if (IsA(cdr_o, CONS))
    {
	printf(" ");
	WriteCons(cdr_o);
    }
    else if (cdr_o == nil)
	return;
    else
    {
	printf(" . ");
	write(cdr_o);
    }
}
