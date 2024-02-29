#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define MAX 10000

int main(int argc, char *argv[])
{
	float *generate_arr(size_t);

	int myid, numprocs, i;
	double startwtime = 0.0, endwtime;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	startwtime = MPI_Wtime();
	// MPI Start
	float *arr = generate_arr(MAX);
	float sum = 0;
	float total = 0;

	for (i = 0; i < MAX; ++i)
	{
		sum = sum + arr[i];
	}

	MPI_Reduce(&sum, &total, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		endwtime = MPI_Wtime();
		printf("Total sum: %.3f\n", total);
	}

	MPI_Finalize();
	return 0;
}

float *generate_arr(size_t n)
{
	float *arr = malloc(n * sizeof(float));

	for (float *p = arr; p < arr + n; p++)
		*p = rand() / 10.0;

	return arr;
}
