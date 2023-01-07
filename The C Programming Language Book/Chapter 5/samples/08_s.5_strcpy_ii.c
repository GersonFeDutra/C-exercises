#include <stdio.h>
#include <stdlib.h>


/* strcpy: copy t to s: pointer version 1 */
void strcpy(char *s, const char *t)
{
    while ((*s = *t) != '\0')
        s++, t++;
}


int main(void)
{
    char str[13];
    strcpy(str, "Hello World!");
    printf("%s\n", str);

    return EXIT_SUCCESS;
}
