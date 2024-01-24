#include <stdlib.h>
#include <stddef.h>

long *l_generate(size_t n, long max)
{
    long *l = malloc(sizeof(long) * n);

    for (long *p = l, *q = l + n; p != q; p++)
        *p = rand() % max;

    return l;
}

int *i_generate(size_t n, int max)
{
    int *i = malloc(sizeof(int) * n);

    for (int *p = i, *q = i + n; p != q; p++)
        *p = rand() % max;

    return i;
}
