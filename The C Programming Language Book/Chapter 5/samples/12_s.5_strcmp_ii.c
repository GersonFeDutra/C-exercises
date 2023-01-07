#include <stdio.h>
#include <stdlib.h>


/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t: pointer version */
int str_cmp(const char *s, const char *t)
{
    for (; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;

    return *s - *t;
}


#define printd(expr) printf(#expr ": %d\n", expr)
int main(void)
{
    printd(str_cmp("Hello World!", "Hello Friends!"));

    return EXIT_SUCCESS;
}
