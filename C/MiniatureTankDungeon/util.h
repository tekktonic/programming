#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#define ORDIE(v, message) do{if (!(v)) {fprintf(stderr, "%s\n", (message));}}while(0)
#endif
