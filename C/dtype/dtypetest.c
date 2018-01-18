#include <dtype.h>

int main(void)
{
    List l = new_List(1, NULL);

    printf("%d\n", List_pop(&l));

    return 0;
}
