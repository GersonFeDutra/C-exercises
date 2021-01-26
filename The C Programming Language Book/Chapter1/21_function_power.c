#include <stdio.h>

int power(int m, int n);
// int oldpower(); /* Declaração de uma função da antiga ANSI C. */

int main()
{
    int i;

    // printf("%d\n", oldpower(12, 2));

    for (i = 0; i < 10; ++i)
        printf("%d %d %d\n", i, power(2, i), power(-3, i));
    
    return 0;
}


/* power: raise base to n-th power; n >= 0 */
int power(int base, int n)
{
    int i, p = 1;

    for (i = 1; i <= n; ++i)
        p *= base;
    
    return p;
}


/* Antiga definição de uma função do padrão ANSI C */
// oldpower(base, n)
// int base, n;
// {
//     int i, p;
//     p = 1;
//
//     for (i = 1; i <= n; ++i)
//         p *= base;
//    
//     return p;
// }
