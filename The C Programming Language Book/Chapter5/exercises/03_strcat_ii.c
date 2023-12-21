#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* strcat: concatenate t to end of s; s must be big enough: pointer version */
void str_cat(char s[], const char t[])
{
    while (*s) /* move to '\0' in s */
        s++;

    while (*s++ = *t++); /* copy t */
}


int main(int argc, char const *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "\033[31mError! Two strings must be passed as arguments.\033[m\n");
        return EXIT_FAILURE;
    }

    char s[strlen(argv[1]) + strlen(argv[2]) + 1];
    strcpy(s, argv[1]); // copy argv[1] to s

    str_cat(s, argv[2]); // concat s with argv[2]
    printf("%s\n", s);

    return 0;
}
