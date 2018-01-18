#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "cons.h"
#include "globals.h"
#include "parselib.h"
#include "value.h"


int main(int argc, char *argv[])
{
    printf("%s %f\n", name, version);
    
    while (1)
    {
        char *in = readline(name "> ");
        add_history(in);
        printf("%s\n", in);
        if (*in != ';')
        {
            struct value test = read_value(in);
            
            print_value_debug(stdout, &test);
        }
        free(in);
    }
    return 0;
}
