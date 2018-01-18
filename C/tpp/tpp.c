#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *includepath[] = { "/include" /* hey, I like simple hierarchies and this makes Tengen work nicely */ , "/usr/include", "/usr/local/include"};

const char *supportedtokens[] = {"include", "ifdef", "ifndef", "endif", "define", "undef"};

size_t strlcpy(char *dst, const char *src, size_t length)
{
    int i = 0; 
    for(; i < (length - 1) && src[i]; i++) {
	dst[i] = src[i];
    }
    dst[i] = '\0';
    return i + 1;
}

struct ht {
    char *values[BUCKET_SIZE];
    char *keys[BUCKET_SIZE];
    struct ht *next;
};

int dumbhash(char *input)
{
    unsigned int ret = 0;
    for(;*input;input++)
    {
	ret += *input;
    }
    return ret % BUCKET_SIZE;
}

void htchange(struct ht new, const char *key, const char *value)
{
    int hash = dumbhash(key);

    if (new.values[i])
    {
	if (strcmp(new.values[i], key) != 0)
	{
	    
	}
    }
    	size_t len = strlen(key) + 1;
	new.values[i]
	(void)strlcpy(new)
}
