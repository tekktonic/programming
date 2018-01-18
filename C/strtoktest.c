#include <string.h>
#include <stdio.h>

int main(void)
{
    char *string = malloc(512);
    scanf("%s\n", string);

    char *str1, *str2;

    str1 = strtok(string, ":");
    str2 = strtok(NULL, ":");

    printf("%s %s", str1, str2);
} 
