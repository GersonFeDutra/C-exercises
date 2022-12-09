#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* reverse: reverse string s in place */
void reverse(char s[])
{
    char c;
    int i, j;

    /*for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }*/

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c; // reverse operation as a single expression.
}


int main(int argc, char const *argv[])
{
    int len = 255;

    if (argc == 2)
        len = atoi(argv[2]);
    else
        fprintf(stderr, "\033[33mWarning! Buffer size not informed, using default (255).\033[m\n");

    char s[len];
    int i, c;

    for (i = 0; (c = getchar()) != EOF && i < len - 1; ++i)
        s[i] = c;
    s[i] = '\0';

    reverse(s);

    printf("%s\n", s);

    return EXIT_SUCCESS;
}
