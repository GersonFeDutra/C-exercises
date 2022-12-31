#include <stdio.h>
#include <stdlib.h>

/* printd: print n in decimal */
void printd(int n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}


int main(int argc, char const *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "\033[31mError: Expected at least one integer argument.\n\033[m");

        return EXIT_FAILURE;
    }
    int sum = atoi(argv[1]);

    fprintf(stderr, "\033[34m%d", sum);

    for (int i = 2; i < argc; ++i) {
        int d = atoi(argv[i]);
        sum += d;
        fprintf(stderr, " + %d", d);
    }
    fprintf(stderr, " = \033[m");

    printd(sum);
    putchar('\n');

    return EXIT_SUCCESS;
}
