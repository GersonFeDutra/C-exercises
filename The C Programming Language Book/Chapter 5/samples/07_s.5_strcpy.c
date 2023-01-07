#include <stdio.h>
#include <stdlib.h>


/* strcpy: copy t to s: array subscript version */
void strcpy(char *s, const char *t)
{
    int i;

    i = 0;
    while ((s[i] = t[i]) != '\0')
        i++;
}


int main(void)
{
    char str[13];
    strcpy(str, "Hello World!");
    printf("%s\n", str);

    return EXIT_SUCCESS;
}
