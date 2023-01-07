#include <stdio.h>
#include <stdlib.h>


/* strcat: concatenate t to end of s; s must be big enough. */
void strcat(char s[], const char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0') /* find end of s */
        i++;

    while ((s[i++] = t[j++]) != '\0'); /* copy t */
}


int main(int argc, char const *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "\033[31mError! Two strings must be passed as arguments.\033[m\n");
        return EXIT_FAILURE;
    }

    int n = 0;
    for (int i = 0; argv[1][i] != '\0'; ++i)
        ++n;

    for (int i = 0; argv[2][i] != '\0'; ++i)
        ++n;

    char s[n + 1];
    for (int i = 0; argv[1][i] != '\0'; ++i)
        s[i] = argv[1][i]; // copy argv[1] to s

    strcat(s, argv[2]);
    printf("%s\n", s);

    return 0;
}
