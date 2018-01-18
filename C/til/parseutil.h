#include <string.h>
#ifndef PARSEUTIL_H
#define PARSEUTIL_H
#include <stdbool.h>
#include <ctype.h>

bool isdelim(char c);

bool isinitial(char c);

char peek(FILE *f)

void chomp(FILE *fp)

#endif
