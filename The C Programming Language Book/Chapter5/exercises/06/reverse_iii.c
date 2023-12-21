#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* reverse: reverse string s in place: pointer version */
void reverse(char *s)
{
    char c, *t = s;
    size_t m = 0;

    while (*(t + m) != '\0')
        m++; /* find size of string */

    for (t += m - 1, m /= 2; m != 0; m--, s++, t--)
        c = *s, *s = *t, *t = c; // reverse operation as a single expression.
}


int main(int argc, char const *argv[])
{
    int len = 255;

    if (argc == 2)
        len = atoi(argv[2]);
    else
        fprintf(stderr, "\033[33m""Warning! Buffer size not informed, "
                "using default (%d).\033[m\n", len);

    char s[len];
    int i, c;

    for (i = 0; (c = getchar()) != EOF && i < len - 1; ++i)
        s[i] = c;
    s[i] = '\0';

    reverse(s);

    printf("%s\n", s);

    return EXIT_SUCCESS;
}
