#include "utils.h"
#include "benchmark.h"
#include "generator.h"
#include <stddef.h>
#include <time.h>
#include <omp.h>
#include <stdio.h>

#define N_STEPS 100000000

/* Compare o desempenho do exercício da aproximação do pi, utilizando os métodos:
- ~Laço paralelo~;
- Região Crítica com critical
- Região Crítica com atomic
- Tarefas independentes (sections)
Aproximação do pi, com sincronização: <https://github.com/rafaelperazzo/cc0021/blob/master/codigo/07_aproximacao_pi_sincronizacao.c>
 */
int main(void)
{
    void pi_serial(int), pi_parallel(int);
    void pi_critical(int), pi_atomic(int);
    void pi_sections(int);

    time_t t;
    srand((unsigned) time(&t)); // Starting random number generator

    start("Serial");
    pi_serial(N_STEPS);

//     back("Parallel");
//     pi_parallel(N_STEPS);

    back("Critical");
    pi_critical(N_STEPS);

    back("Atomic");
    pi_atomic(N_STEPS);

    back("Sections");
    pi_sections(N_STEPS);

	benchmark(max(omp_get_num_procs() - 1, 1), true);
}

void pi_serial(int num_steps)
{
    double sum, x, step, pi;
    step = 1.0 / (double) num_steps;
    sum = 0.0f;

    for (int i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step; // Rectangle width
        sum = sum + 4.0 / (1.0 + x * x); // Sum += Rectangle area
    }
    stop();
    pi = step * sum;
    printf("PI = %f\n", pi);
}


void pi_parallel(int num_steps)
{
    double sum, x, step, pi;
    step = 1.0 / (double) num_steps;
    sum = 0.0f;

    int n_threads = max(1, omp_get_num_procs() - 1);
#pragma omp parallel private(x) num_threads(n_threads)
{
#pragma omp for reduction (+:sum)
    for (int i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step; // Rectangle width
        sum = sum + 4.0 / (1.0 + x * x); // Sum += Rectangle area
    }
}
    stop();
    pi = step * sum;
    printf("PI = %f\n", pi);
}


void pi_critical(int num_steps)
{
    double sum, x, step, pi;
    step = 1.0 / (double) num_steps;
    sum = 0.0f;

	int n_threads = max(1, omp_get_num_procs() - 1);
#pragma omp parallel private(x) num_threads(n_threads)
{
#pragma omp for
{
    for (int i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step; // Rectangle width
#pragma omp critical
        sum = sum + 4.0 / (1.0 + x * x); // Sum += Rectangle area
    }
}
}
    stop();
    pi = step * sum;
    printf("PI = %f\n", pi);
}


void pi_atomic(int num_steps)
{
    double sum, x, step, pi;
    step = 1.0 / (double) num_steps;
    sum = 0.0f;

	int n_threads = max(1, omp_get_num_procs() - 1);
#pragma omp parallel private(x) num_threads(n_threads)
{
#pragma omp for
{
    for (int i = 0; i < num_steps; i++) {
        x = (i + 0.5) * step; // Rectangle width
#pragma omp atomic
        sum = sum + 4.0 / (1.0 + x * x); // Sum += Rectangle area
    }
}
}
    stop();
    pi = step * sum;
    printf("PI = %f\n", pi);
}


void pi_sections(int num_steps)
{
    double sum, x, step, pi, a, b;
    step = 1.0 / (double) num_steps;
    sum = a = b = 0.0f;

	int n_threads = max(1, omp_get_num_procs() - 1);
#pragma omp parallel private(x) num_threads(n_threads)
{
#pragma omp sections
{
#pragma omp section
{
	for (int i = 0; i < num_steps; i += 2) {
        x = (i + 0.5) * step; // Rectangle width
        a = a + 4.0 / (1.0 + x * x); // Sum += Rectangle area
    }
}
#pragma omp section
{
	for (int i = 1; i < num_steps; i += 2) {
        x = (i + 0.5) * step; // Rectangle width
        b = b + 4.0 / (1.0 + x * x); // Sum += Rectangle area
    }
}
}
}
    stop();
    sum = a + b;
    pi = step * sum;
    printf("PI = %f\n", pi);
}
