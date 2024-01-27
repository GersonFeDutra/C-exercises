#include "benchmark.h"
#include "utils.h"
#include <omp.h>
#include "generator.h"

#define THRESHOLD 20
#define MAX 300

/* Escreva um programa em C, que teste o funcionamento de cada um dos tipos de scheduling
apresentados anteriormente. Utilize 20 iterações para um melhor entendimento.
<http://jakascorner.com/blog/2016/06/omp-for-scheduling.html>
- static: partes iguais
- dynamic: aleatório
- guided: em partes iguais
- auto: automático
 */
#include <stdio.h>
int main(void)
{
    unsigned threads = max(omp_get_num_procs() - 1, 1);
	long *times = l_generate(THRESHOLD, MAX);

	start("Serial");
	for (int i = 0; i <= THRESHOLD; i++)
	{
		msleep(times[i]);
	}

	next("Default");
#pragma omp parallel for num_threads(threads)
	for (int i = 0; i <= THRESHOLD; i++)
	{
		msleep(times[i]);
	}

	next("Static");
#pragma omp parallel for num_threads(threads) schedule(static)
	for (int i = 0; i <= THRESHOLD; i++)
	{
		msleep(times[i]);
	}

	next("Dynamic");
#pragma omp parallel for num_threads(threads) schedule(dynamic)
	for (int i = 0; i <= THRESHOLD; i++)
	{
		msleep(times[i]);
	}

	next("Guided");
#pragma omp parallel for num_threads(threads) schedule(guided)
	for (int i = 0; i <= THRESHOLD; i++)
	{
		msleep(times[i]);
	}

	next("Auto");
#pragma omp parallel for num_threads(threads) schedule(auto)
	for (int i = 0; i <= THRESHOLD; i++)
	{
		msleep(times[i]);
	}
	benchmark(threads, true);
}
