#ifndef STAS_PARSEHELP_H
#define STAS_PARSEHELP_H

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

gboolean IsA_Delimiter(gchar c);
gboolean IsA_Initial(gchar c);

gchar peek(FILE *file);

void chomp(FILE *fp);

#endif
