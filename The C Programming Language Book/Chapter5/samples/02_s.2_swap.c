#include <stdio.h>
#include <stdlib.h>


void swap(int *px, int *py)
{
    int tmp;

    tmp = *px;
    *px = *py;
    *py = tmp;
}


int main(void)
{
    int a = 1, b = 2;

    return EXIT_SUCCESS;
}
