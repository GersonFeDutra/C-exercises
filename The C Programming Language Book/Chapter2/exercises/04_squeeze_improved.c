#include <stdio.h>
#include <stdlib.h>

#define TRUE 1


/* squeeze: delete all c from s */
void squeeze(char s1[], const char s2[])
{
    int i, j;

    for (i = j = 0; s1[i] != '\0'; i++) {
        int skip = TRUE;
        for (int k = 0; s2[k] != '\0'; k++)
            if (skip = s1[i] == s2[k])
                break;
        if (!skip)
            s1[j++] = s1[i];
    }

    s1[j] = '\0';
}


#define BUF_SIZE 255
/* Write an alternate version of squeeze(s1, s2) that deletes each
 * character in s1 that matches any character in the string s2. */
int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "\033[33m"
                "Error! Expects a string of characters as a command line argument.\n\033[m");
        return EXIT_FAILURE;
    }

    unsigned int i = 0;
    int c;
    char s[BUF_SIZE];

    while ((c = getchar()) != EOF) {
        s[i++] = c;

        if (i == BUF_SIZE || c == '\n') {
            s[i] = '\0';
            squeeze(s, argv[1]);
            printf("%s", s);
            i = 0;
        }
    }

    if (i != 0) {
        s[i] = '\0';
        squeeze(s, argv[1]);
        printf("%s\n", s);
    }

    return EXIT_SUCCESS;
}
