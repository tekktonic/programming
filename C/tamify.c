//#include <sys/tame.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    int flags = 0;

    int ch;
    while ((ch = getopt(argc, argv, "Ml")) != -1)
    {
        switch(ch) {
        case 'l':
            printf("l!\n");
            break;
        case 'M':
            printf("M!\n");
        }
        
    }
}
