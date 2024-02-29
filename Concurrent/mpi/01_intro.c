#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	// Iniciando MPI
	MPI_Init(NULL, NULL);

	int n_cpus;
	MPI_Comm_size(MPI_COMM_WORLD, &n_cpus);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Start MPI

	int number;

	if (rank == 0)
	{
		// Send number to rank 1
		number = 100;
		// MPI_Send(buff,count, dtype, dest, tag, comm)
		MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("Data sent\n");
	}
	else if (rank == 1)
	{
		// Receive from 0
		int received = 0;
		// MPI_Recv(buff, count, dtype, src, tag, comm, status);
		MPI_Recv(&received, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Data received: %d\n", received);
	}

	// End MPI
	MPI_Finalize();
}
