#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char **argv)
{
    printf("%c %d\n", *argv[0], *argv[0] == '-');
//    if (*argv[0] == '-')
    //  {
	printf("Login!\n");
	printf("And the password is...? ");
	char *answer = malloc(64 * sizeof(*answer));
	fgets(answer, 63, stdin);
	if (strcmp(answer, "foobar\n") == 0)
	    execl("/bin/bash", "-bash", 0);
	printf("Nope!\n");
	exit(1);
//}

    execl("/usr/bin/bash", "bash", 0);

    return 0;
}
