#include <omp.h>
#include <stdio.h>

int main(void) {
#pragma omp parallel num_threads(4) // Região paralela
{
  printf("Hello world from thread %d!\n", omp_get_thread_num());
}
}
