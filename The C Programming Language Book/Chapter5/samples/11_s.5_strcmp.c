#include <stdio.h>
#include <stdlib.h>


/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int str_cmp(const char *s, const char *t)
{
    int i;

    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 0;

    return s[i] - t[i];
}


#define printd(expr) printf(#expr ": %d\n", expr)
int main(void)
{
    printd(str_cmp("Hello World!", "Hello Friends!"));

    return EXIT_SUCCESS;
}
