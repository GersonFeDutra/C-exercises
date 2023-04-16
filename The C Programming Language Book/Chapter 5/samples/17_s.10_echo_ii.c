#include <stdio.h>
#include <stdlib.h>


/* echo command-line arguments; 2nd version */
int main(int argc, char const *argv[])
{
    while (--argc > 0)
        // printf("%s%s", *++argv, argc > 1 ? " " : "");
        printf(argc > 1 ? "%s " : "%s", *++argv);
        /* using an expression as the 1st argument of printf as an alternative */
    putchar('\n');

    return EXIT_SUCCESS;
}
