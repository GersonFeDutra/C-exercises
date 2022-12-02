#include <stdio.h>
#include <stdlib.h>


/* lower: convert c to lower case; ASCII only */
int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}


/* Rewrite the function `lower`, with a conditional expression instead of if-else. */
int main(void)
{
    int c;

    while ((c = getchar()) != EOF)
        putchar(lower(c));

    return EXIT_SUCCESS;
}
