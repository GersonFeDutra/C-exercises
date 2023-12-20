#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100


int main(void)
{
    double sum, v;

    sum = 0;
    while (scanf("%lf", &v) == 1)
        printf("\t%g\n", sum += v);

    return EXIT_SUCCESS;
}
