#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../lib/generator.h"
#include "../lib/benchmark.h"
#include "../lib/utils.h"

static long N = 100000000;
static int _UNITY = sizeof(double);
#define MAX N
#define ROOT 0

int main(int argc, char *argv[])
{
	// Iniciando MPI
	MPI_Init(&argc, &argv);
	int nprocs;
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//MPI_Status status;

	double *data = malloc(sizeof(double) * N); // Allocate some memory on each rank
	const double p = 1.0 / N; // probability

	if (data == NULL)
		MPI_Abort(MPI_COMM_WORLD, -1);

	if (rank == ROOT) {
		fprintf(stderr, "\033[33m"
						"Loading...\n\033[m");
		// Generate random numbers on rank 0
		randomize();
		d_generate_at(data, N, MAX);
    }

	// Broadcast the data from rank 0 to all other ranks
    MPI_Bcast(data, N, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);

	if (rank == ROOT) {
		/* Serial execution */
		double mi = 0.0, std_deviation = 0.0;

		fprintf(stderr, "\33[2K\033[A\r"); // clear line
		start_group("Serial", "Hope (mi)");

		for (double *x = data; x != data + N; x++)
			mi += *x;

		mi *= p;
		stop();
		printf("\tHope (mi): %.7f\n", mi);

		back("Standard deviation");

		for (double *x = data; x < data + N; x++) {
			register float diff = *x - mi;
			std_deviation += diff * diff;
		}
		std_deviation = sqrt(p * std_deviation);

		stop();
		printf("\tStandard deviation: %.7f\n", std_deviation);
	}

	double mi_partial = 0.0, mi_total;	   // hope
	double std_dev_partial = 0.0, std_dev_total; // standard deviation

	/*
	INICIO
	*/

	if (rank == ROOT)
		next_group("Parallel", "Hope (mi)");

	MPI_Barrier(MPI_COMM_WORLD);

	for (double *x = data + rank; x < data + N; x += nprocs)
		mi_partial += *x;

	MPI_Reduce(&mi_partial, &mi_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	mi_total *= p;

	MPI_Bcast(&mi_total, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	//printf("rank %d: %.7f\n", rank, mi_total);

	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == ROOT)
		stop();

	//printf("\t# rank %d: %.7f\n", rank, mi_total); // debug

	if (rank == ROOT) {
		printf("\tHope (mi): %.7f\n", mi_total);
		back("Standard deviation");
	}

	for (double *x = data + rank; x < data + N; x += nprocs)
	{
		register float diff = *x - mi_total;
		std_dev_partial += diff * diff;
	}
	MPI_Reduce(&std_dev_partial, &std_dev_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
		stop();
	//printf("\t# rank %d: %.7f\n", rank, std_dev_total); // debug

	if (rank == 0) {
		std_dev_total = sqrt(p * std_dev_total);
		printf("\tStandard deviation: %.7f\n", std_dev_total);
	}

	// TODO -> Check
	// MPI_Bcast(&std_dev_total, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	/*
	FIM
	*/
	if (rank == 0) {
		free(data);
		benchmark(nprocs, true);
	}

	MPI_Finalize();

	return 0;
}
