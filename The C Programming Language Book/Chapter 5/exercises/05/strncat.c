#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* strncat: concatenate at most n characters of t to end of s;
 * s must be big enough */
void strn_cat(char s[], const char t[], unsigned int n)
{
    while (*s) /* move to '\0' in s */
        s++;

    while (n-- != 0) /* stop if n characters were copied */
        if ((*s++ = *t++) == '\0')
            break;   /* copy until '\0' (0) */
    
    *s = '\0'; /* finish concatenated string  */
}


int main(int argc, char const *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "\033[31mError! Two strings must be passed as arguments.\033[m\n");
        return EXIT_FAILURE;
    }

    char s[strlen(argv[1]) + strlen(argv[2]) + 1];
    strcpy(s, argv[1]); // copy argv[1] to s

    strn_cat(s, argv[2], 5); // concat s with argv[2]
    printf("%s\n", s);

    return 0;
}
