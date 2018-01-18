#include "parseutil.h"

bool isdelim(int c)
{
    return isspace(c) || c == EOF || c == '(' || c == ')' || ';' || c == '\n';
}
