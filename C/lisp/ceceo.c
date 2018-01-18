#include "ceceo.h"


GHashTable *global;
gint depth; // our current depth in the sexp



gboolean IsA(Object *o, Type type)
{
    return (gboolean)o->type == type;
}


void Init()
{
    t = new_Object();
    f = new_Object();
    nil = new_Object();

    t->type = BOOL;
    f->type = BOOL;
    nil->type = NIL;

    t->data.Bool.truthiness = 't';
    f->data.Bool.truthiness = 'f';

}

// ---------- no longer defining types, string parsey-manipulatey stuff here-----


Object *ReadBool(FILE *fp)
{
    gchar c = getc(fp);
    if (c == 't')
	return t;
    else if (c == 'f')
	return f;
    else
    {
	fprintf(stderr, "Invalid boolean %c, must be t or f\n", c);
	exit(1);
    }
}

Object *read(FILE *fp)
{
    gchar c;
    chomp(fp);

    c = (gchar)getc(fp);
    if (g_ascii_isdigit(c) || (c == '-' && g_ascii_isdigit(peek(fp))))
    {
	ungetc(c, fp);
	return ReadNum(fp);
    }
    else if (c == '"')
    {
	// no need to unget in this case
	return ReadString(fp);
    }
    else if (c == ':')
	return ReadLiteral(fp);
    else if (c == '#')
	return ReadBool(fp);
    else if (c == '(')
    {
	return ReadCons(fp);
    }
    else
    {
	fprintf(stderr, "unexpected character '%c'\n", c);
	exit(1);
    }

    fprintf(stderr, "Somehow got into illegal state!\n");
    exit(1);
}


Object *eval(Object *exp)
{
    return exp;
}

void WriteBool(Object *boolean)
{
    g_printf("#%c", boolean->data.Bool.truthiness);
}

void write(Object *exp)
{
    switch (exp->type)
    {
    case NUM:
	WriteNum(exp);
	break;
    case STR:
	WriteString(exp);
	break;
    case LIT:
	WriteLiteral(exp);
	break;
    case BOOL:
	WriteBool(exp);
	break;
    case CONS:
	printf("(");
	WriteCons(exp);
	printf(")");
	break;
    default:
	fprintf(stderr, "Tried to print unknown type\n");
	exit(1);
    }
}

void Free(Object *obj)
{
    switch (obj->type)
    {
    case NUM:
	del_Num(obj);
	break;
    case STR:
	del_String(obj);
	break;
    case LIT:
	del_Literal(obj);
	break;
    }
}

// ----- now for the fun
int main(void)
{
    global = g_hash_table_new(g_str_hash, g_str_equal);

    Object *obj;
    Init();
    while(1)
    {
	printf("` ");
	obj = eval(read(stdin));
	write(obj);
	Free(obj);
	printf("\n");
    }

    return 0;
}
