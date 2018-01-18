#include "entity.h"
void EnableEntities(const char *name, Entity *constructor(json_t* args), ...)
{
    char *n = name;
    (Entity *constr)(json_t *args);
    va_list args;

    FHash_insert(constructors, name, constr);
    va_start(args, constructor);
    for(int i = 1; n != NULL; i++)
    {
	printf("%s\n", n);
	n = va_arg(args, char*);
	i++;
	constr = va_arg(args, (Entity *)(json_t *args));
	FHash_insert(constructors, n, constr);
    }
}
