#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#include "person.h"

int main(int argc, char **argv)
{
    
    srand(time(NULL));
    struct person p = new_person();
    p.dumper.dump(&p);
}
