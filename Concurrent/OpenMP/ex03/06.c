#include "benchmark.h"
#include "generator.h"
#include "utils.h"
#include <omp.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#define SIZE 100000000
#define MAX 1024

/*
- Escreva um programa em C, com OpenMP, que encontre o maior valor de um vetor aleatório.
- Escreva um programa em C, com OpenMP, que encontre o índice do maior valor de um vetor aleatório.
*/
int main(void)
{
    randomize();
    printf("Loading...\n");

    unsigned threads = max(omp_get_num_procs() - 1, 1);
    int *arr = i_generate(SIZE, MAX);
    int higher;
    size_t higherId;
    size_t count = 0;

    start("Serial");
    higher = *arr;
    higherId = 0;
    for (int *p = arr + SIZE; p != arr; p--)
        if (*p > higher) {
            higher = *p;
            higherId = p - arr;
        }
    stop();
    printf("\tThe higher value %d was found at index %lu\n", higher, higherId);
    count = 0;

    back("Parallel");
    higher = *arr;
    higherId = 0;
#pragma omp parallel num_threads(threads)
    {
    #pragma omp for
    for (int *p = arr + SIZE; p != arr; p--)
        if (*p > higher) {
    #pragma omp critical
            if (*p > higher) {
                higher = *p;
                higherId = p - arr;
            }
        }
    }
    stop();
    printf("\tThe higher value %d was found at index %lu\n", higher, higherId);

    benchmark(threads, true);
}
