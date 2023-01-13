#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int comp1(int a, int b) {
    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}


int comp2(int a, int b) {
    return (a - b) / abs(a - b);
}


/* test an algorithm time using combinations of some integer sample data of the given length */
int test(int (*alg)(int, int), int samples[], int len)
{
    void print_duration(clock_t start, clock_t end);
    clock_t start, end;

    fprintf(stderr, "\033[34m""Start!\033[m\n");
    start = clock();

    for (int i = 0; i < len; ++i)
        for (int j = 0; j < len; ++j)
            (*alg)(samples[i], samples[j]);

    end = clock();
    fprintf(stderr, "\033[34m""End!\033[m\n");

    double clocks = end - start;
	printf("Elapsed time: %.3fs.\n", clocks / CLOCKS_PER_SEC);
	// printf("Elapsed time: %lu clocks\n", end - start);

    return clocks;
}


/* shortcut to test comparison function */
#define comp(c, s, len, clk) { printf(#c ":\n"); clk = test((int (*)(int, int)) c, s, len); putchar('\n'); }
int main(void)
{
    double percent(double[], int n);

    /* sqrt(1GB) de dados aleatórios */
    const unsigned long LEN = (unsigned long) pow(2, 15);
    int samples[LEN];
    for (int i = 0; i < LEN; ++i)
        samples[i] = rand();

    double clocks[2];
    comp(comp1, samples, LEN, clocks[0]);
    comp(comp2, samples, LEN, clocks[1]);
    percent(clocks, 2);

    printf("comp1: %.1f%%\n", clocks[0] * 100);
    printf("comp2: %.1f%%\n", clocks[1] * 100);
    putchar('\n');

    return EXIT_SUCCESS;
}


double percent(double arr[], int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
        sum += arr[i];

    while (n-- > 0)
        *arr++ = *arr / sum;
}
