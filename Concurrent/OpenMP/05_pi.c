#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

void serial_pi();
void parallel_pi();

#define N_STEPS 100000000
#define MAX(A, B) (((A) > (B)) ? (A) : (B))


int main () {
    time_t t;
    srand((unsigned) time(&t)); // Starting random number generator

    printf("Starting serial approximation!\n");
	double start, end, t_serial, t_parallel;

    start = omp_get_wtime();
    serial_pi(N_STEPS);
    end = omp_get_wtime();
    t_serial = end - start;
    printf("Time serial: %f\n", t_serial);

	printf("\nStarting parallel approximation!\n");
	start = omp_get_wtime();
    parallel_pi(N_STEPS);
    end = omp_get_wtime();
	t_parallel = end - start;
    printf("Time parallel: %f\n", t_parallel);

    double speedup = t_serial / t_parallel;
    printf("\nSpeedup: %.4f\n", speedup);
    printf("Efficiency: %.4f\n", speedup / THREADS_N);
}


void serial_pi(int num_steps)
{
    double sum, x, step, pi;
    step = 1.0 / (double) num_steps;
    sum = 0.0f;

    for (int i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step; // Rectangle width
        sum = sum + 4.0 / (1.0 + x * x); // Sum += Rectangle area
    }
    pi = step * sum;
    printf("PI = %f\n", pi);
}


void parallel_pi(int num_steps)
{
    double sum, x, step, pi;
    step = 1.0 / (double) num_steps;
    sum = 0.0f;

    int n_procs = MAX(1, omp_get_num_procs() - 1);
#pragma omp parallel private(x) num_threads(n_procs)
    {
    #pragma omp for reduction (+:sum)
        for (int i = 0; i < num_steps; i++) {
            x = (i + 0.5) * step; // Rectangle width
            sum = sum + 4.0 / (1.0 + x * x); // Sum += Rectangle area
        }
    }
    pi = step * sum;
    printf("PI = %f\n", pi);
}
