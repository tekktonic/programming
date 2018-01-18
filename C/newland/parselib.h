#ifndef PARSELIB_H
#define PARSELIB_H
#include <stdbool.h>
#include "value.h"

bool is_delimeter(char c);
struct value read_value(const char *string);


#endif
