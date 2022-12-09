#include <stdio.h>
#include <stdlib.h>


/* binsearch: find x in v[0] <= v[i]  <= .. <= v[n-1] */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;

        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }

    return -1; /* no match */
}


#define LEN 10
int main(void)
{
    int v[LEN];

    putchar('[');
    int i;
    for (i = 0; i + 1 < LEN; ++i)
		printf("%d, ", v[i] = i * 3);

    printf("%d]\n", v[i] = i * 3);

    int searches[] = {3, 7, 9};

    for (int i = 0; i < 3; ++i) {
        int p = binsearch(searches[i], v, LEN);

        if (p == -1)
            fprintf(stderr, "\033[31m%d not found!\033[m\n", searches[i]);
        else
            printf("Index of %d: %d\n", searches[i], p);
    }

    return EXIT_SUCCESS;
}
