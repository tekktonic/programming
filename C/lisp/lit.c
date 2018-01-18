#include "sym.h"

Object *new_Literal(GString *lit)
{
    Object *ret = new_Object();
    ret->type = LIT;
    ret->data.Literal.literal = lit;
    return ret;
}

void del_Literal(Object *obj)
{
    g_string_free(obj->data.Literal.literal, TRUE);
    free(obj);
}

Object *ReadLiteral(FILE *fp)
{
	GString *str = g_string_new("");
	gchar c;

	while(!feof(fp))
	{
	    if (!IsA_Delimiter((c = getc(fp))))
		g_string_append_c(str, c);
	    else
	    {
		Object *ret = new_Literal(str);
		return ret;
	    }
	}
	exit(1);
}

void WriteLiteral(Object *lit)
{
    g_printf(":%s", lit->data.Literal.literal->str);
}
