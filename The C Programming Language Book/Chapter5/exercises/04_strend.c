#include <stdio.h>
#include <stdlib.h>


/* strend: returns 1 if the string t occurs at the end of the string s, and 0 otherwise */
int strend(const char *s, const char *t)
{
    const char *_s = s;
    const char *_t = t;

    while (*t) { /* moves to '\0' in t, and carries s */
        if (*s == '\0')
            return 0; /* s is not large enough */
        t++, s++;
    }

    while (*s)
        s++; /* moves to '\0' in s */

    for (; _t != t; s--, t--)
        if (*s != *t)
            return 0;

    return *s == *t;
}


int main(int argc, char const *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "\033[31mError! Two strings must be passed as arguments.\033[m\n");
        return EXIT_FAILURE;
    }

    if (strend(argv[1], argv[2])) {
        fprintf(stderr, "\033[32m""arg2 is at the end of arg1\033[m\n");
        return EXIT_SUCCESS;
    }
    else {
        fprintf(stderr, "\033[33m""arg2 is not at the end of arg1\033[m\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
