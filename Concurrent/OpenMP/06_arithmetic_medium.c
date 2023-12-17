#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 99999999
#define THREADS_N 4

void serial_medium(int *, size_t);
void parallel_medium(int *, size_t);


int main () {
    time_t t;
    srand((unsigned) time(&t)); // Starting random number generator

    // Must allocate on heap, otherwise results in segfault
    int *array = malloc(sizeof(int) * SIZE);

    for (int *p = array + SIZE; p != array; )
		*--p = rand();

    printf("Starting serial medium!\n");
	double start, end, t_serial, t_parallel;

    start = omp_get_wtime();
    serial_medium(array, SIZE);
    end = omp_get_wtime();
    t_serial = end - start;
    printf("Time serial: %f\n", t_serial);

    printf("\nStarting parallel medium!\n");
    start = omp_get_wtime();
    parallel_medium(array, SIZE);
    end = omp_get_wtime();
	t_parallel = end - start;
    printf("Time parallel: %f\n", t_parallel);

    double speedup = t_serial / t_parallel;
    printf("\nSpeedup: %.4f\n", speedup);
    printf("Efficiency: %.4f\n", speedup / THREADS_N);
}


void serial_medium(int *at, size_t len)
{
    long long sum = 0.0;

	for (int *p = at; p != at + len; p++)
		sum += *p;

    printf("Medium: %Ld\n", sum / len);
}


void parallel_medium(int *at, size_t len)
{
    long long sum = 0.0;
#pragma omp parallel num_threads(THREADS_N)
    {
    #pragma omp for reduction (+:sum)
        for (int *p = at; p != at + len; p++)
            sum += *p;

    }
    printf("Medium: %Ld\n", sum / len);
}
