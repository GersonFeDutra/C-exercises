#include <stdio.h>

int power(int m, int n);


/* test power function */
int main()
{
    int i;
    printf(" i | ^2 | ^-3\n");

    for (i = 0; i < 10; ++i)
        printf("%3d %3d %3d\n", i, power(2, i), power(-3, i));
    
    return 0;
}


/* power: raise base to n-th power; n >= 0 */
int power(int base, int n)
{
    int p;

    for (p = 1; n > 0; --n)
        p *= base;

    return p;
}

