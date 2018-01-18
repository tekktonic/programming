#include "stringutil.h"
#include <stdio.h>

void strsplit(const char *string, char split, SplitString ret)
{
    SplitString cur = ret;
    int begin = 0;
    int end = 0;
    while(*string)
    {
	printf("%c\n", *string);
	if (*string == split)
	{
	    printf("splitting!\n");
	    printf("%d %d\n", begin, end);
	    cur->string = malloc(sizeof(char) * (end - begin));
	    if (!cur->string)
		exit(1);
//	    printf("%p\n", cur->string);
	    for(short i = begin; i < end; ++i)
	    {
		*(cur->string) = string[i];
//		printf("%c %c\n", *cur->string, string[i]);
		++(cur->string);
	    }

//	    printf("%s\n", string);
//	    printf("%p\n", cur->string);
	    begin = end;
	    cur->next = malloc(sizeof(*cur));
	    cur = cur->next;
	    cur->string = NULL;
	    cur->next = NULL;
	}
	++string;
	++end;
    }
    // now catch the last bit of the split
    cur->next = malloc(sizeof(*cur));
    cur->next = cur;
    cur->string = malloc(sizeof(char) * (end - begin));
    printf("%d %d\n", begin, end);
    for (short i = begin; i < end; ++i)
    {
	*cur->string = string[i];
	++cur->string;
    }
}
