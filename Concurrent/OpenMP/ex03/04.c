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
    void sections_medium(int *, size_t), sections3_medium(int *, size_t);

    threads_num = max(omp_get_num_procs() - 1, 1);
    printf("Loading...\n");
    randomize();

    int *arr = i_generate(SIZE, SIZE);

    start("Serial");
    serial_medium(arr, SIZE);

//     back("Parallel");
//     parallel_medium(arr, SIZE);

    back("Critical");
    critical_medium(arr, SIZE);

    back("Atomic");
    atomic_medium(arr, SIZE);

    back("Sections (2)");
    sections_medium(arr, SIZE);

    back("Sections (3)");
    sections3_medium(arr, SIZE);

    benchmark(threads_num, true);
}


void serial_medium(int *at, size_t len)
{
    long long sum = 0.0;

	for (int *p = at; p < at + len; p++)
		sum += *p;

    stop();
    printf("\tMedium: %Ld\n", sum / len);
}


// void parallel_medium(int *at, size_t len)
// {
//     long long sum = 0.0;
// #pragma omp parallel num_threads(threads_num)
//     {
//     #pragma omp for reduction (+:sum)
//         for (int *p = at; p < at + len; p++)
//             sum += *p;
// 
//     }
//     stop();
//     printf("\tMedium: %Ld\n", sum / len);
// }


void critical_medium(int *at, size_t len)
{
    long long sum = 0.0;
#pragma omp parallel num_threads(threads_num)
    {
    #pragma omp for
    for (int *p = at; p < at + len; p++)
        #pragma omp critical
        sum += *p;
    }
    stop();
    printf("\tMedium: %Ld\n", sum / len);
}


void atomic_medium(int *at, size_t len)
{
	long long sum = 0.0;
#pragma omp parallel num_threads(threads_num)
    {
    #pragma omp for
    for (int *p = at; p < at + len; p++)
        #pragma omp critical
        sum += *p;
    }
    stop();
    printf("\tMedium: %Ld\n", sum / len);
}


void sections_medium(int *at, size_t len)
{
	long long sum, a, b;
    sum = a = b = 0;
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
    }
    sum = a + b;
    stop();
    printf("\tMedium: %Ld\n", sum / len);
}

void sections3_medium(int *at, size_t len)
{
	long long sum, a, b, c;
    sum = a = b = c = 0;
#pragma omp parallel num_threads(threads_num)
    {
    #pragma omp sections
    {
        #pragma omp section
        for (int *p = at + 0; p < at + len; p += 3)
            a += *p;
        #pragma omp section
        for (int *p = at + 1; p < at + len; p += 3)
            b += *p;
        #pragma omp section
        for (int *p = at + 2; p < at + len; p += 3)
            c += *p;
    }
    }
    sum = a + b + c;
    stop();
    printf("\tMedium: %Ld\n", sum / len);
}
