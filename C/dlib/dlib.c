#include "dlib.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>



size_t d_hash_string(DValue v, size_t modulus)
{
    size_t ret;

    for(char *str=string; *str; str++)
    {
        ret += *str;
    }

    return ret % modulus;
}
