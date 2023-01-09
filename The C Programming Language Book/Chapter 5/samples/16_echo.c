#include <stdio.h>
#include <stdlib.h>


/* echo command-line arguments; 1st version */
int main(int argc, char const *argv[])
{
    int i;

    for (int i = 1; i < argc; ++i)
        printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
    putchar('\n');

    return EXIT_SUCCESS;
}
