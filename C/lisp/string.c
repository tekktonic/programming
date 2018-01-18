#include "string.h"


Object *new_String(GString *str)
{
    Object *ret = new_Object();
    ret->type = STR;
    ret->data.String.string = str;

    return ret;
}

void del_String(Object *str)
{
    g_string_free(str->data.String.string, TRUE);
    free(str);
}

Object *ReadString(FILE *fp)
{
	GString *str = g_string_new("");
	gchar c;

	while(!feof(fp))
	{
	    if ((c = getc(fp)) != '"')
		g_string_append_c(str, c);
	    else
	    {
		Object *ret = new_String(str);
		return ret;
	    }
	}
	fprintf(stderr, "Unterminated string!\n");
	exit(1);
}


void WriteString(Object *str)
{
    g_printf("%s", str->data.String.string->str);
}
