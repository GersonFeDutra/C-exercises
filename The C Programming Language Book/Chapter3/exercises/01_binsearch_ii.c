#include "time.h"
#include "limits.h"
#include <stdio.h>
#include <stdlib.h>


/* binsearch: find x in v[0] <= v[i]  <= .. <= v[n-1] */
int binsearch2(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;

	while (x != v[mid = ((low + high) / 2)] && low < high) {

        if (x < v[mid])
            high = mid - 1;
		else
			low = mid + 1;
	}

	if (x == v[mid])
        return mid;

	return -1; /* no match */
}


#define LEN 10
/* Our binary search makes two tests inside the loop, when one would suffice
 * (at the price of more tests outside). Write a version with only one test
 * inside the loop and measure difference in run-time.
 */
int main(void)
{
    int binsearch1(int x, int v[], int n);
	int v[LEN];

	putchar('[');
	int i;
	for (i = 0; i + 1 < LEN; ++i)
		printf("%d, ", v[i] = i * 3);

	printf("%d]\n", v[i] = i * 3);

	int searches[] = {3, 7, 9};

    int(* bin_searches[])(int, int[], int) = {
        &binsearch1,
        &binsearch2,
    };

	for (int i = 0; i < 2; ++i) {
        printf("Starting %d°s searches:\n", i + 1);

        clock_t begin = clock();

        for (int j = 0; j < 0x1ffffff; ++j)
            for (int k = 0; k < 3; ++k) {
                int p = bin_searches[i](searches[k], v, LEN);

                // if (p == -1)
                //     fprintf(stderr, "\033[31m%d not found!\033[m\n", searches[k]);
                // else
                //     printf("Index of %d: %d\n", searches[k], p);
            }

        clock_t end = clock();
        long long unsigned int clocks = end - begin;
        printf("\033[34mElapsed time: %lu clocks.\033[m\n", clocks);
    }

	return EXIT_SUCCESS;
}


/* binsearch: find x in v[0] <= v[i]  <= .. <= v[n-1] */
int binsearch1(int x, int v[], int n)
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
