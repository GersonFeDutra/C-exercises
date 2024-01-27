#include "benchmark.h"
#include "generator.h"
#include "utils.h"
#include <omp.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#define SIZE 100000000
#define MAX 255

/* Escreva um programa serial e paralelo em C, com OpenMP, que dado um vetor de inteiros e um valor
x, encontrar quantas vezes x ocorre no vetor. Calcular as métricas de desempenho.
<https://github.com/rafaelperazzo/cc0021/blob/43304d9196b3e796aadabc7cfa1c509d646fb646/codigo/soma_divisores_vetor.c>
*/
int main(void)
{
    randomize();
    printf("Loading...\n");

    unsigned threads = max(omp_get_num_procs() - 1, 1);
    int *arr = i_generate(SIZE, MAX);
    int target = rand() % MAX;
    size_t count = 0;

    start("Serial");
    for (int i = 0; i < SIZE; ++i)
        if (arr[i] == target)
            count++;
    stop();
    printf("\t%d was found %lu times\n", target, count);
    count = 0;

    back("Parallel");
#pragma omp parallel num_threads(threads)
    {
    #pragma omp for reduction(+:count)
    for (int i = 0; i < SIZE; ++i)
        if (arr[i] == target)
            count++;
    }
    stop();
    printf("\t%d was found %lu times\n", target, count);

    benchmark(threads, true);
}
