#include "t_list.h"

#include <stdarg.h>

t_list t_list_new(void *first, ...)
{
    t_list ret;

    va_list args;

    va_start(args, first);

    t_list *now = *ret;

    now->cur = cur;
    
    for (void *cur = first; cur != NULL; cur = va_arg(args, void*))
    {
        now->next = calloc(1, sizeof(t_list));
        now->next->prev = now;
        now = now->next;
        now->cur = cur;
    }
}
