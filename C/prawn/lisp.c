#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


/* MODEL */
typedef enum
{
    NUMBER,
    CHARACTER,
    NIL,
    PAIR,
    SYMBOL,
    BOOLEAN
}object_type;

typedef struct object
{
    object_type type;
    union
    {
	struct
	{
	    double val;
	}number;

	struct
	{
	    bool val;
	}boolean;

	struct
	{
	    char val;
	}character;

	struct
	{
	}nil;

	struct
	{
	    struct object *car;
	    struct object *cdr;
	}pair;

	struct
	{
	    char *val;
	}symbol;
    }data;
}object;


object *car(object *obj);
object *cdr(object *obj);

object *cons(object *car, object *cdr);

object *t, *f, *nil, *symbol_table;

object *alloc_object(void)
{
    object *ret;
    ret = malloc(sizeof(object));
    if(!ret)
    {
	fprintf(stderr, "OOM!\n");
	exit(1);
    }
    return ret;
}

void *dealloc_object(object *obj) // We only have non-allocated objects for now, so just free the struct
{
    free(obj);
}

object *make_number(double value)
{
    object *ret = alloc_object();
    ret->type = NUMBER;
    ret->data.number.val = value;
    return ret;
}

object *make_boolean(bool value)
{
    object *ret = alloc_object();
    ret->type = BOOLEAN;
    ret->data.boolean.val = value;
    return ret;
}

object *make_character(char value)
{
    object *ret = alloc_object();
    ret->type = CHARACTER;
    ret->data.character.val = value;
    return ret;
}

object *make_nil(void)
{
    object *ret = alloc_object();
    ret->type = NIL;
    return ret;
}

/*
object *make_symbol(char *value)
{
    object *ret;
    object *element;

    element = symbol_table;

    while(!is_nil(element))
    {
	if(!strcmp((car(element)->data.symbol.val), value))
	{
	    return car(element);
	}
	element = cdr(element);
    }

    ret = alloc_object();
    ret->type = SYMBOL;
    ret->data.symbol.val = malloc(strlen(value) + 1);

    if(!ret->data.symbol.val)
    {
	fprintf(stderr, "OOM!\n");
	exit(1);
    }

    strcpy(ret->data.symbol.val, value);
    symbol_table = cons(ret, symbol_table);

    return ret;
}*/

object *cons(object *car, object *cdr)
{
    object *ret = alloc_object();
    ret->type = PAIR;
    ret->data.pair.car = car;
    ret->data.pair.cdr = cdr;
    return ret;
}

bool is(object *obj, object_type type)
{
    return obj->type == type;
}

bool is_true(object *obj)
{
    return obj == t;
}

bool is_false(object *obj)
{
    return !is_true(obj);
}

object *car(object *obj)
{
    if (is(obj, PAIR))
	return obj->data.pair.car;

    fprintf(stderr, "Attempted to car a non-pair");
    exit(1);
}

object *cdr(object *obj)
{
    if (is(obj, PAIR))
	return obj->data.pair.cdr;
    fprintf(stderr, "Attempted to cdr a non-pair");
    exit(1);
}

void set_car(object *obj, object *val)
{
    if(is(obj, PAIR))
	obj->data.pair.car = val;
    else
    {
	fprintf(stderr, "Attempted to set car of a non-pair");
	exit(1);
    }
}

void set_cdr(object *obj, object *val)
{
    if(is(obj, PAIR))
	obj->data.pair.car = val;
    else
    {
	fprintf(stderr, "Attempted to set cdr of a non-pair");
	exit(1);
    }
}

void init(void)
{
    t = make_boolean(true);
    f = make_boolean(false);
    nil = make_nil();
}

/* READ */
bool is_delimiter(int c)
{
    return isspace(c) || c == EOF || c == '(' || c == ')' || c == '"' || c == ';';
}

bool is_initial(int c)
{
    return isalpha(c);
}

int peek(FILE *in)
{
    int c = getc(in);
    ungetc(c, in);
    return c;
}

void chomp(FILE *in)
{
    int c;

    while ((c = getc(in)) != EOF)
    {
	if (isspace(c))
	    continue;
	else if (c == ';')
	{
	    while(((c = getc(in)) != EOF) && (c != '\n')); // ignore comments until EOF or end of line
	    continue;
	}
	ungetc(c, in);
	break;
    }
}

object *read(FILE *in);

object *read_pair(FILE *in)
{
    int c;
    object *car_obj;
    object *cdr_obj;

    chomp(in);
    c = getc(in);

    if (c == ')')
    {
	return nil;
    }
    ungetc(c, in);

    car_obj = read(in);

    chomp(in);
    c = getc(in);
    if (c == '.')
    {
	if (!is_delimiter(peek(in)))
	{
	    fprintf(stderr, "Full stop not followed by a delimiter");
	    exit(1);
	}
	cdr_obj = read(in);
	chomp(in);
	c = getc(in);
//	printf("%c\n", c);
	if (c != ')')
	{
	    return nil;
	}
	return cons(car_obj, cdr_obj);
    }
    else
    {
	ungetc(c, in);
	cdr_obj = read_pair(in);
	return cons(car_obj, cdr_obj);
    }
}

	    
object *read(FILE *in)
{
    int c;
    short sign = 1;
    double num = 0;

    chomp(in);
    c = getc(in);

    if (c == '#')
    {
	c = getc(in);
	switch(c)
	{
	case 't':
	    return t;
	case 'f':
	    return f;
	case '\'':
	    c = getc(in);//get the character

	    {
		if (c == '\\')
		{
		    switch (c = getc(in))
		    {
		    case 'n':
			c = '\n';
			break;
		    case 't':
			c = '\t';
			break;
		    case '0': // future FFI, anyone?
			c = '\0';
			break;
		    }

		    if (peek(in) != '\'')
		    {
			fprintf(stderr, "invalid special character!\n");
			exit(1);
		    }
		}
	    }
	    getc(in);
	    return make_character(c);
	    break;
	default:
	    fprintf(stderr, "Unknown bool. did you mean to have a comment? that's ';'\n");
	    exit(1);
	}
    }

    else if (isdigit(c) || (c == '-' && (isdigit(peek(in)))))
    {
	if (c == '-')
	{
	    sign = -1;
	}
	else
	{
	    ungetc(c, in);
	}
	while(isdigit(c = getc(in)))
	{
	    num = (num * 10) + (c - '0');
	}
	num *= sign;

	if (is_delimiter(c))
	{
	    ungetc(c, in);
	    return make_number(num);
	}

	else
	{
	    fprintf(stderr, "Num not followed by a delimiter\n");
	    exit(1);
	}
    }

    else if (c == 'n')
    {
	if (getc(in) == 'i')
	    if (getc(in) == 'l')
		return nil;
	fprintf(stderr, "you started with 'n' but you didn't say nil?\n");
	exit(1);
    }

    else if (c == '(')
    {
	return read_pair(in);
    }

    else
    {
	fprintf(stderr, "unexpected %c\n", c);
    }
    fprintf(stderr, "Somehow got into an illegal state\n");
    exit(1);
}

/* EVAL */
object *eval(object *exp)
{
    return exp; // so far we only have self-evaluating types
}

/* PRINT */
void write(object *obj);

void write_pair(object *obj)
{
    object *car_obj;
    object *cdr_obj;

    car_obj = car(obj);
    cdr_obj = cdr(obj);

    write(car_obj);

    if (cdr_obj->type == PAIR)
    {
	printf(" ");
	write_pair(cdr_obj);
    }

    else if (cdr_obj->type = NIL)
	return;
    else
    {
	printf(" . ");
	write(cdr_obj);
    }
}

void write(object *obj)
{
    switch (obj->type)
    {
    case BOOLEAN:
	printf("#%c", is_true(obj) ? 't' : 'f');
	break;

    case CHARACTER:
	printf("#'%c", obj->data.character.val);
	break;
    case NUMBER:
	printf("%f", obj->data.number.val);
	break;
    case NIL:
	printf("nil");
	break;
    case PAIR:
	printf("(");
	write_pair(obj);
	printf(")");
	break;
    default:
	fprintf(stderr, "Unknown type\n");
	exit(1);
    }
}

/* LOOP */

int main(int argc, char **argv)
{
    init();
    while (true)
    {
	printf("prawn> ");
	object *cur = eval(read(stdin));
	write(cur);
	dealloc_object(cur);
	printf("\n");
    }

    return 0;
}
