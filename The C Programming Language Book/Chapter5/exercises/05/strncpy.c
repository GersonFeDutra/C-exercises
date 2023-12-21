#include <stdio.h>
#include <stdlib.h>


/* strncpy: copy at most n characters from t to s */
void strncpy(char *s, const char *t, unsigned int n)
{
    while (n-- != 0) /* stop if n characters were copied */
        if ((*s++ = *t++) == '\0')
            break;   /* copy until '\0' (0) */

    *s = '\0'; /* finish copied string */
}


int main(void)
{
    char str[13];
    strncpy(str, "Hello World!", 5u);
    printf("%s\n", str);

    return EXIT_SUCCESS;
}
