#include <stdio.h>
#include <stdlib.h>


/* lower: convert c to lower case; ASCII only */
int lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}


int main(void)
{
    int c;

    while ((c = getchar()) != EOF)
        putchar(lower(c));

    return EXIT_SUCCESS;
}
