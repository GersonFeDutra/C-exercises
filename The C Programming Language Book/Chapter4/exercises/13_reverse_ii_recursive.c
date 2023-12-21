#include <stdio.h>
#include <stdlib.h>


/* auxiliar recursive method of reverse */
int _reverse(char s[], int i)
{
    if (s[i] == '\0')
        return 0;

    int j = _reverse(s, i + 1);

    if (i > j) { /* swap */
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }

    return j + 1;
}


/* reverse: reverse string s in place. version 2: recursive */
void reverse(char s[])
{
    if (s[0] != '\0')
        _reverse(s, 1);
}


int main(int argc, char const *argv[])
{
    int len = 255;

    if (argc == 2)
        len = atoi(argv[2]);
    else
        fprintf(stderr,
                "\033[33mWarning! Buffer size not informed, using default (%d).\033[m\n", len);

    char s[len];
    int i, c;

    for (i = 0; (c = getchar()) != EOF && i < len - 1; ++i)
        s[i] = c;
    s[i] = '\0';

    reverse(s);

    printf("%s\n", s);

    return EXIT_SUCCESS;
}
