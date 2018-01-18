#include "num.h"
#include "parsehelp.h"

Object *new_Num(gchar *str)
{
    Object *ret = new_Object();
    ret->type = NUM;
    mpf_init(ret->data.Num.num);
    mpf_set_str(ret->data.Num.num, str, 10);
    return ret;
}

void del_Num(Object *num)
{
    mpf_clear(num->data.Num.num);
    free(num);
}

Object *ReadNum(FILE *fp)
{
    gchar c = getc(fp);
    gboolean decimal_hit = FALSE;
    GString *token = g_string_new("");

    g_string_append_c(token, c); // since we matched the Number case, we already know that it's safe to add

    while(g_ascii_isdigit((gint)(c = getc(fp))) || (c == '.' && g_ascii_isdigit(peek(fp))))
    {
	if (c == '.')
	{
	    if (decimal_hit)
	    {
		fprintf(stderr, "Number has more than 1 decimal point!\n");
		exit(1);
	    }
	    else
		decimal_hit = TRUE;
	}
	g_string_append_c(token, c);
    }
    if (IsA_Delimiter(c))
    {
	ungetc(c, fp);
	Object *ret = new_Num(token->str); // right now this just catches numbers at the repl, no need for them to be mut
	g_string_free(token, TRUE);
	return ret;
    }
    else
    {
	fprintf(stderr, "Number not followed by delimiter\n");
	exit(1);
    }
}

void WriteNum(Object *num)
{
    gmp_printf("%Ff", num->data.Num.num);
}
