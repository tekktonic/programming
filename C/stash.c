#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


typedef struct
{
    char *string;
    int length;
}SaneString;

void SaneString_alloc(SaneString *target, size_t size)
{
    if (!target->string) // if we need to allocate a new string
	target->string = malloc(sizeof(char) * size);
    else
	target->string = realloc(target->string, sizeof(char) * size);

    target->length = size / sizeof(char);
}
	

void skipSpaces(FILE *fp) // stdin, usually
{
    char c;
    while ((c = getc(fp)) == ' ')
    {}
    ungetc(c, fp);
}

int main(int argc, char **argv)
{
    uid_t usr;
    struct passwd *pw = NULL;
    SaneString lineBuf;

    lineBuf.string = malloc(512);
    lineBuf.length = 512;

    usr = geteuid();
    pw = getpwuid(usr);
    setenv("USER", pw->pw_name, true);
    setenv("HOME", pw->pw_dir, true);

    while (true)
    {
	char *cwd = malloc(512);
	char *arg = malloc(512);

	getcwd(cwd, 511);
	printf("%s\n", cwd);
	memset(lineBuf.string, 0, 512);
//	printf("%s:%s$ ", pw->pw_name, cwd);
	fgets(lineBuf.string, 511, stdin);
	lineBuf.length = strlen(lineBuf.string);


	if (lineBuf.string[0] == 'c' && lineBuf.string[1] == 'd')
	{
	    printf("Changing directory from: ");
	    int i = 3;
	    for(;lineBuf.string[i] != ' '; i++);
	    strncpy(arg, lineBuf.string + 3, 511);
	    printf("%s\n to: %s\n", getenv("PWD"), arg);
	    chdir(arg);
	}
    }

    return 0;
}
