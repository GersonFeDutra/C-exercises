#include <stdio.h>

#define printd(expr) printf(#expr ": %d", expr);


int main(void)
{
    // printf("%d %d %d %d\n", sizeof(char), sizeof(short), sizeof(int), sizeof(long));
    // printf("%d %d %d %d\n", sizeof(char), sizeof(short int), sizeof(int), sizeof(long int));
    // printf("%d %d %d %d\n", sizeof(char), sizeof(float), sizeof(double), sizeof(long double));

    printd(sizeof(char));
    putchar(' ');
    printd(sizeof(short));
    putchar(' ');
    printd(sizeof(int));
    putchar(' ');
    printd(sizeof(long));
    putchar(' ');
    printd(sizeof(long long));
    printf("\n\n");

    printd(sizeof(unsigned char));
    putchar('\n');
    printd(sizeof(unsigned short));
    putchar('\n');
    printd(sizeof(unsigned int));
    putchar('\n');
    printd(sizeof(unsigned long));
    putchar('\n');
    printd(sizeof(unsigned long long));
    printf("\n\n");

    printd(sizeof(float));
    putchar('\n');
    printd(sizeof(double));
    putchar('\n');
    printd(sizeof(long double));
    printf("\n\n");

    printd(sizeof(void *));
    putchar('\n');

    return 0;
}
