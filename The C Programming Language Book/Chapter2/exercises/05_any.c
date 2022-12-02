#include <stdio.h>
#include <stdlib.h>

#define TRUE 1


/* Any
 * Returns: the first location in the string s1 where any character from
 * the string s2 occurs, or -1 if s1 contains no characters from s2.
 */
int any(char s1[], const char s2[])
{
    int i;

    for (i = 0; s1[i] != '\0'; i++)
        for (int j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                return i;

    return -1;
}


#define BUF_SIZE 5
/* Write the function any(s1, s2), that is equivalent to the standard library function
 * strpbrk (excepts the stdlib version returns a pointer to the location). */
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
    int bpos = -1;
    unsigned long int at = 0;

    while ((c = getchar()) != EOF) {
        s[i++] = c;

        if (i == BUF_SIZE || c == '\n') {
            s[i] = '\0';
            bpos = any(s, argv[1]);
            i = 0;

            if (bpos != -1)
                break;
            else
                at += BUF_SIZE;
        }
    }

    if (bpos != -1)
        while ((c = getchar()) != EOF);
    else if (i != 0) {
        s[i] = '\0';
        bpos = any(s, argv[1]);
    }

	if (bpos == -1)
        printf("%d\n", bpos);
    else
        printf("%lu\n", bpos + (unsigned long) at);

	return EXIT_SUCCESS;
}
