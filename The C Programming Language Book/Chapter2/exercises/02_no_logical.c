#include <stdio.h>
#include <stdlib.h>

/*
 * Write a loop equivalent to the for loop below without using && or ||.
 *  for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
 *      s[i] = c;
 */
int main(int argc, char const *argv[])
{
    int i = 0, c, lim = 250;
    char s[lim];

    while (i < lim - 1) {
        if ((c = getchar()) == '\n')
            break;
        if (c == EOF)
            break;
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    printf("%s\n", s);

    return 0;
}
