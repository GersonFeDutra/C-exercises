#include "../lib/benchmark.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define bool short

#define ROOT 0
#define N 1000000

int main(int argc, char *argv[]) {
	bool *generate_binary_array(int n);

    //Iniciando MPI
    MPI_Init(&argc, &argv);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

	if (rank == ROOT)
		fprintf(stderr, "\033[33m"
						"Loading...\n\033[m");

	// Broadcast the same seed to all ranks
	long t = time(NULL);
	MPI_Bcast(&t, 1, MPI_LONG, ROOT, MPI_COMM_WORLD);
    srand(t);

    bool *file = generate_binary_array(N);

    size_t count = 0;

	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == ROOT) {
		fprintf(stderr, "\33[2K\033[A\r"); // clear last line
		start("Serial");

		for (bool *p = file; p < file + N; p++)
			if (*p)
				count++;

		stop();
		printf("\t""Parity: %d\n", count % 2 == 0);

		back("Parallel");
	}

	unsigned long c_partial = 0, c_total;
	MPI_Barrier(MPI_COMM_WORLD);
    /*
    INICIO
    */

	for (bool *p = file + rank; p < file + N; p += nprocs)
		if (*p)
			c_partial++;

	MPI_Reduce(&c_partial, &c_total, 1, MPI_UNSIGNED_LONG, MPI_SUM, ROOT, MPI_COMM_WORLD);

	if (rank == ROOT) {
		stop();
		printf("\t""Parity: %d\n", c_total % 2 == 0);
	}

    /*
    FIM
    */

    MPI_Finalize();

	if (rank == ROOT)
		benchmark(nprocs, true);

    return 0;
}


bool *generate_binary_array(int n) {
	bool *arr;
	int i;
	arr = (bool *)malloc(sizeof(bool) * n);
	for (i=0; i < n; i++) {
		int num = rand() % 2;
		arr[i] = num;
	}
	return arr;
}
