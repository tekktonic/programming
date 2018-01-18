#include "parsehelp.h"

gboolean IsA_Delimiter(gchar c)
{
    return (gboolean)(g_ascii_isspace(c) || c == EOF || c == '(' || c == ')' || c == ';' || c == '\n');
}

gboolean IsA_Initial(gchar c)
{
    return (gboolean)(g_ascii_isalpha(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '>' || c == '<' || c == '=');
}

gchar peek(FILE *file)
{
    gchar ret = (gchar)getc(file); // yep, I'm using gchars with standard lib functions. why? because it's easier than glib in this case.
    ungetc(ret, file);
    return ret;
}

void chomp(FILE *fp)
{
    gchar c;

    while(!feof(fp))
    {
	c = (gchar)getc(fp);

	if (g_ascii_isspace(c))
	    continue;
	else if (c == '/' && peek(fp) == '/') 
	{
	    while ((c = (gchar)getc(fp) != EOF) && (c != '\n')) // read until end of the line-comment
		continue;
	}
	else if (c == EOF)
	{
	    printf("\n");
	    exit(0);
	}
	ungetc(c, fp); // got a useful char
	break;
    }
}

