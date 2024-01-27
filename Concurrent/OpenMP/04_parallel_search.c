#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 99999999

/* Note: fixed threads num not recommended */
// #define THREADS_N 4

void serial_search(int, int *, size_t);
void parallel_search(int, int *, size_t);

int main () {
    time_t t;
    srand((unsigned) time(&t)); // Starting random number generator

    int n  = 123456;

    // Must allocate on heap, otherwise results in segfault
    int *array = malloc(sizeof(int) * SIZE);

    for (int *p = array + SIZE; p != array; )
		*--p = rand();
    array[SIZE / 4 * 3] = n; // force element in array

    printf("Starting serial search!\n");
	double start, end, t_serial, t_parallel;

    start = omp_get_wtime();
    serial_search(n, array, SIZE);
    end = omp_get_wtime();
    t_serial = end - start;
    printf("Time serial: %f\n", t_serial);

    printf("\nStarting parallel search!\n");
    start = omp_get_wtime();
    parallel_search(n, array, SIZE);
    end = omp_get_wtime();
	t_parallel = end - start;
    printf("Time parallel: %f\n", t_parallel);

    double speedup = t_serial / t_parallel;
    printf("\nThreads used: %d\n", omp_get_num_procs());
    printf("Speedup: %.4f\n", speedup);
    printf("Efficiency: %.4f\n", speedup / omp_get_num_procs());
}


void serial_search(int n, int *at, size_t len)
{
	for (int *p = at; p < (at + len); p++) {
		if (*p == n) {
			printf("Thread[%d] ACHOU: %d\n", omp_get_thread_num(), *p);
			// break;
		}
    }
}


void parallel_search(int n, int *at, size_t len)
{
    char flag = 0;
#pragma omp parallel for shared(flag) num_threads(omp_get_num_procs()) 
    for (int *p = at; p < (at + len); p++) {
        if (flag) continue;
        if (*p == n) {
            printf("Thread[%d] ACHOU: %d\n", omp_get_thread_num(), *p);
        }
    }
}
