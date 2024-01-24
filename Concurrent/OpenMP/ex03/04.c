#include "utils.h"
#include "benchmark.h"
#include "generator.h"
#include <stddef.h>
#include <time.h>
#include <omp.h>
#include <stdio.h>

#define SIZE 99999999

static unsigned threads_num;

/* Compare o desempenho do exercício da média aritmética de um vetor, utilizando os métodos:
- ~Laço paralelo;~
- Região Crítica com critical
- Região Crítica com atomic
- Tarefas independentes (sections)
*/
int main(void)
{
    void serial_medium(int *, size_t), parallel_medium(int *, size_t);
    void critical_medium(int *, size_t), atomic_medium(int *, size_t);
    void sections_medium(int *, size_t);


    time_t t;
    srand((unsigned) time(&t)); // Starting random number generator
    threads_num = max(omp_get_num_procs() - 1, 1);

    int *arr = i_generate(SIZE, SIZE);

    start("Serial");
    serial_medium(arr, SIZE);

//     back("Parallel");
//     parallel_medium(arr, SIZE);

    back("Critical");
    critical_medium(arr, SIZE);

    back("Atomic");
    atomic_medium(arr, SIZE);

    back("Sections");
    sections_medium(arr, SIZE);

    benchmark(threads_num, true);
}


void serial_medium(int *at, size_t len)
{
    long long sum = 0.0;

	for (int *p = at; p != at + len; p++)
		sum += *p;

    stop();
    printf("Medium: %Ld\n", sum / len);
}


// void parallel_medium(int *at, size_t len)
// {
//     long long sum = 0.0;
// #pragma omp parallel num_threads(threads_num)
//     {
//     #pragma omp for reduction (+:sum)
//         for (int *p = at; p != at + len; p++)
//             sum += *p;
// 
//     }
//     stop();
//     printf("Medium: %Ld\n", sum / len);
// }


void critical_medium(int *at, size_t len)
{
    long long sum = 0.0;
#pragma omp parallel num_threads(threads_num)
{
#pragma omp for
{
    for (int *p = at + omp_get_thread_num(); p < at + len; p += omp_get_num_threads())
#pragma omp critical
        sum += *p;
}
}
    stop();
    printf("Medium: %Ld\n", sum / len);
}


void atomic_medium(int *at, size_t len)
{
	long long sum = 0.0;
#pragma omp parallel num_threads(threads_num)
{
#pragma omp for
{
    for (int *p = at + omp_get_thread_num(); p < at + len; p += omp_get_num_threads())
#pragma omp critical
        sum += *p;
}
}
    stop();
    printf("Medium: %Ld\n", sum / len);
}


void sections_medium(int *at, size_t len)
{
	long long sum = 0.0, a, b;
#pragma omp parallel num_threads(threads_num)
{
#pragma omp sections
{
#pragma omp section
    for (int *p = at + 0; p < at + len; p += 2)
        a += *p;
#pragma omp section
    for (int *p = at + 1; p < at + len; p += 2)
        b += *p;
}
    sum = a + b;
}
    stop();
    printf("Medium: %Ld\n", sum / len);
}
