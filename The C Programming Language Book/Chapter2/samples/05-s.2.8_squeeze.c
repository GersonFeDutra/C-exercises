#include <stdio.h>
#include <stdlib.h>


/* squeeze: delete all c from s */
void squeeze(char s[], int c)
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];

    s[j] = '\0';
}


#define BUF_SIZE 255
int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "\033[33mError! Expects a character as a command line argument.\n\033[m");
        return EXIT_FAILURE;
    }

    unsigned int i = 0;
    int c;
    char s[BUF_SIZE];

    while ((c = getchar()) != EOF) {
        s[i] = c;
        i++;

        if (i == BUF_SIZE) {
            squeeze(s, argv[1][0]);
            printf("%s", s);
            i = 0;
        }
    }

    if (i != 0) {
        squeeze(s, argv[1][0]);
        printf("%s\n", s);
    }

    return EXIT_SUCCESS;
}
