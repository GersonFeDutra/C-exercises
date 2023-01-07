#include <stdio.h>
#include <stddef.h>


/* strlen: return length of string s. version 3 */
size_t strlen(char *s)
{
    char *p = s;

    while (*p != '\0')
        p++;

    return p - s;
}


/* prints the length of the string constant, uses Ld to read an large enough value */
#define pr_len(str) printf(#str " length: %Ld.\n", strlen(str))
int main(void)
{
    pr_len("Hello World");

    return 0;
}
