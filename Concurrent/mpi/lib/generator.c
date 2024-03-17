#include <mpi.h>
#include <stdlib.h>
#include <stddef.h>

float *f_generate(size_t n, float max)
{
    float *f = malloc(sizeof(float) * n);

    if (f == NULL)
        MPI_Abort(MPI_COMM_WORLD, 1);

    for (float *p = f, *q = f + n; p != q; p++)
        // Read <https://stackoverflow.com/a/13409133> for reference
        *p = (float)rand() / (float)(RAND_MAX / max);

    return f;
}

double *d_generate(size_t n, double max)
{
    double *d = malloc(sizeof(double) * n);

    if (d == NULL)
        MPI_Abort(MPI_COMM_WORLD, 1);

    for (double *p = d, *q = d + n; p != q; p++)
        // Read <https://stackoverflow.com/a/13409133> for reference
        *p = (double)rand() / (double)(RAND_MAX / max);

    return d;
}

void d_generate_at(double *at, size_t n, double max)
{
    if (at == NULL)
        MPI_Abort(MPI_COMM_WORLD, 1);

    for (double *p = at, *q = at + n; p != q; p++)
        // Read <https://stackoverflow.com/a/13409133> for reference
        *p = (double)rand() / (double)(RAND_MAX / max);
}
