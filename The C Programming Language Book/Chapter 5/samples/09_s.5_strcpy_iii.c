#include <stdio.h>
#include <stdlib.h>


/* strcpy: copy t to s: pointer version 2 */
void strcpy(char *s, const char *t)
{
    while ((*s++ = *t++) != '\0'); // notice that comparing to nill is redundant.
        /* copy */
}


int main(void)
{
    char str[13];
    strcpy(str, "Hello World!");
    printf("%s\n", str);

    return EXIT_SUCCESS;
}
