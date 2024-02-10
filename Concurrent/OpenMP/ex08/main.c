#include "generator.h"
#include "utils.h"
#include "benchmark.h"
#include <stdio.h>
#include <omp.h>

#define N 100000000
#define MAX 1000
#define LAMBDA 13.0

/* Escreva um programa com OpenMP que ache e multiplique todos os elementos de
 * um vetor por um escalar e depois achem o maior elemento.
 * Primeiro fazem a multiplicação e depois acham o maior.
 */
int main(void)
{
    fprintf(stderr, "\033[33m""Loading...\n\033[m");
    randomize();

    unsigned threads = max(omp_get_num_procs() - 1, 1);
    float *data = f_generate(N, MAX);
    float *higher;

    printf("Factor: %.3f\n", LAMBDA);
    start("Serial");

    for (float *p = data; p != data + N; p++)
        *p *= LAMBDA;

    higher = data;
    for (float *p = data + 1; p != data + N; p++)
        if (*p > *higher)
            higher = p;

    stop();
    printf("The higher number is %.3f\n", *higher);

    fprintf(stderr, "\033[33m""Loading...\n\033[m");
    for (float *p = data; p != data + N; p++)
        *p /= LAMBDA;

    back("Parallel");

#pragma omp parallel num_threads(threads)
{
    #pragma omp for
    for (float *p = data; p != data + N; p++)
        *p *= LAMBDA;

    higher = data;
    #pragma omp for
    for (float *p = data + 1; p != data + N; p++)
        if (*p > *higher)
            #pragma omp critical
            {
            if (*p > *higher)
                higher = p;
            }
}
    stop();
    printf("The higher number is %.3f\n", *higher);

    benchmark(threads, true);
}
