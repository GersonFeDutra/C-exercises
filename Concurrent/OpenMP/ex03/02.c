#include "benchmark.h"
#include "utils.h"
#include <omp.h>
#include <stdio.h>
#include <time.h>

#define MAX 2000000000
#define MIN 1000000000

/* Escreva um programa em C, com OpenMP, que dado um número maior do que 1.000.000.000 (um bilhão),
calcular a soma de todos os seus divisores.

Utilize os métodos:
- Explicitando uma região crítica
- Redução com for estático
- Redução com for dinâmico
Quais variáveis são compartilhadas entre as threads, e quais são privadas?
<https://github.com/rafaelperazzo/cc0021/blob/43304d9196b3e796aadabc7cfa1c509d646fb646/codigo/soma_divisores_vetor.c>
 */
int main(void)
{
    randomize();
    unsigned threads = max(omp_get_num_procs() - 1, 1);
    unsigned num = rand_range(MIN, MAX);
    unsigned long long sum = 0;

    start("Serial");
    for (int i = num; i > 0; i--)
        if (num % i == 0)
            sum += i;

    stop();
    printf("\ttotal: %llu\n", sum);
	sum = 0;

//     back("Threaded");
// #pragma omp parallel num_threads(threads)
// {
// #pragma omp for
//     for (int i = num; i > 0; i--)
//         if (num % i == 0)
//             sum += i;
// }
//     stop();
//     printf("\ttotal: %llu\n", sum);
// 	sum = 0;

    back("Critic region");
#pragma omp parallel num_threads(threads)
    {
    #pragma omp for
    for (int i = num; i > 0; i--)
        if (num % i == 0)
        #pragma omp critical
            sum += i;
    }
    stop();
    printf("\ttotal: %llu\n", sum);
	sum = 0;

    back("Reduction (default)");
#pragma omp parallel num_threads(threads)
    {
    #pragma omp for reduction(+:sum)
    for (int i = num; i > 0; i--)
        if (num % i == 0)
            sum += i;
    }
    stop();
    printf("\ttotal: %llu\n", sum);
	sum = 0;

    back("Reduction (static)");
#pragma omp parallel num_threads(threads)
    {
    #pragma omp for schedule(static) reduction(+:sum)
    for (int i = num; i > 0; i--)
        if (num % i == 0)
            sum += i;
    }
    stop();
    printf("\ttotal: %llu\n", sum);
	sum = 0;

    back("Reduction (dynamic)");
#pragma omp parallel num_threads(threads)
    {
    #pragma omp for schedule(dynamic) reduction(+:sum)
    for (int i = num; i > 0; i--)
        if (num % i == 0)
            sum += i;
    }
    stop();
    printf("\ttotal: %llu\n", sum);
	sum = 0;

    benchmark(threads, true);
}
