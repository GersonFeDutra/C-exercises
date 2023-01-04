#include <stdio.h>

#define printd(expr) printf(#expr ": %Ld\n", expr);
// prints as a large enough number size so it may work in any machine


int main(void)
{
    int x = 1, y = 2, z[10];
    int *ip;    /* ip is a pointer to int */

    ip = &x;    /* ip now points to x */
    y = *ip;    /* y is now 1 */
    *ip = 0;    /* x is now 0 */
    ip = &z[0]; /* ip now points to z[0] */

    *ip = 2;    /* z at index 0 is now 2 */
    printf("%d %d %d\n", x, y, z[0]);

    // *ip = *ip + 10; /* increments ip by 10 */
    *ip += 10; /* equivalent to the expression above */

    ++*ip;      /* pre-increments whatever ip points to by 1 */
    (*ip)--;    /* post-decrements whatever ip points to by 1 */
    // the parenthesis are necessary, without then it would decrement ip (address) instead
    // because unary operators (like * and ++) associate right to left

    printf("%d %d %d\n", x, y, z[0]);

    int *iq;    /* another pointer to int */
    iq = ip;
    printd(*ip);
    printd(*iq);
    printd(ip);
    printd(iq);

    return 0;
}
