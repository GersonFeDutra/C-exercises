#include <stdio.h>


/* strlen: return length of string s. version 2 */
int strlen(char *s)
{
    int n = 0;

    for (n = 0; *s != '\0'; s++)
        n++;

    return n;
}


#define pr_len(str) printf(#str " length: %d.\n", strlen(str))
int main(void)
{
    pr_len("Hello World");

    return 0;
}
