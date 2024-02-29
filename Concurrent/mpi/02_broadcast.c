#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* #0: pass message to the others
 * #others:
 * - receive message from root
 * - print received value
 */
int main(void)
{
	// Iniciando MPI
	MPI_Init(NULL, NULL);

	int n_cpus;
	MPI_Comm_size(MPI_COMM_WORLD, &n_cpus);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Start MPI
	srand(time(NULL) * rank);

	/*
	int data;

	if (rank == 0)
	{
		// Send data to rank 1
		data = 200;
		// MPI_Bcast(buff,count, dtype, dest, tag, comm)
		MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
	}
	else
	{
		// Receive from 0
		// MPI_Bcast(buff, count, dtype, src, tag, comm, status);
		// MPI_Bcast(&data)
		MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
		printf("Value received: %d\n", data);
	}
	*/

	int data;

	if (rank = 0)
		data = 200;

	MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("Value received: %d\n", data);

	// End MPI
	MPI_Finalize();
}
