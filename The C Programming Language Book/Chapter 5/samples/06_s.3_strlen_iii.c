#include <stdio.h>


/* strlen: return length of string s. version 3 */
int strlen(char *s)
{
    char *p = s;

    while (*p != '\0')
        p++;

    return p - s;
}


#define pr_len(str) printf(#str " length: %d.\n", strlen(str))
int main(void)
{
    pr_len("Hello World");

    return 0;
}
