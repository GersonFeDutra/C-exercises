#include <stdio.h>
#include <stdlib.h>


/* atoi: convert s to integer */
int atoi(const char s[])
{
    int i, n = 0;

    for (int i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');

    return n;
}


/* Sum integers passed as arguments to the program. */
int main(int argc, char const *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "\033[31mNot enough command line argument. Expects at least two integers.\033[m\n");
        return EXIT_FAILURE;
    }

    int t = atoi(argv[1]);
    fprintf(stderr, "\033[34m%d", t);

    for (int i = 2; i < argc; ++i) {
        int x = atoi(argv[i]);
        t += x;
        fprintf(stderr, " + %d", x);
    }

    fprintf(stderr, " = \033[m");
    printf("%d\n", t);

    return EXIT_SUCCESS;
}
