#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include <string.h>
#include <stdlib.h>

typedef struct StringNode
{
    char *string;
    struct StringNode *next;
}StringNode;

typedef StringNode *SplitString;

SplitString strnext(SplitString cur);

void strsplit(const char *string, char split, SplitString ret);
#endif
