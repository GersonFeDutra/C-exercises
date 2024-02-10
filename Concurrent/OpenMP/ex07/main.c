#include "generator.h"
#include "utils.h"
#include "benchmark.h"
#include <stdio.h>
#include <omp.h>
#include <math.h>

#define N 10000000
#define MAX 1000.0

int main(void)
{
    fprintf(stderr, "\033[33m""Loading...\n\033[m");
    randomize();

    unsigned threads = max(omp_get_num_procs() - 1, 1);
    float *data = f_generate(N, MAX);

    const double p = 1.0 / N; // probability
    double mi = 0.0; // hope

    for (float *x = data + N; x-- != data; )
        mi += *x;

    mi *= p;

    printf("Hope (mi): %.3f\n", mi);

    float std_dev; // Standard deviation

    start("Serial");
    std_dev = 0.0;
    for (float *x = data; x < data + N; x++) {
        register float diff = *x - mi;
        std_dev += diff * diff;
    }
    std_dev = sqrt(p * std_dev);
    stop();
    printf("\t""Standard deviation: %.4f\n", std_dev);

    back("Parallel");
    std_dev = 0.0;

#pragma omp parallel num_threads(threads)
    {
    #pragma omp for reduction(+:std_dev)
	for (float *x = data; x < data + N; x++) {
		register float diff = *x - mi;
		std_dev += diff * diff;
	}
    }
    std_dev = sqrt(p * std_dev);
    stop();
    printf("\t""Standard deviation: %.4f\n", std_dev);

    benchmark(threads, true);
}
