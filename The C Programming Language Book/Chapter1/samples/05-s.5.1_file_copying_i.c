#include <stdio.h>


/* copy input to output; 1st version */
int main()
{
    int c; // We use int, so we can hold something big enough that `getchar` returns
           // `EOF` size may be bigger than char

    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }

    return 0; //
}

