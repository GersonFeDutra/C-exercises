#include <stdio.h>
#include <stdlib.h>


/* strcmp: given, at most n characters of s or t;
 * return <0 if s<t, 0 if s==t, >0 if s>t */
int str_cmp(const char *s, const char *t, unsigned int n)
{
    while (n-- != 0)
        if (*s != *t)
            return *s - *t;
        else if (*s == '\0')
            return 0;
        else
            s++, t++;

    return 0;
}


#define printd(expr) printf(#expr ": %d\n", expr)
int main(void)
{
    // printd(str_cmp("Hello World!", "Hello Friends!", 0));
    printd(str_cmp("Hello World!", "Hello Friends!", 5));
    // printd(str_cmp("Hello World!", "Hello Friends!", 255));

    return EXIT_SUCCESS;
}
