#include <omp.h>
#include <stdio.h>

int main(void) {
#pragma omp parallel num_threads(4) // Região paralela
  { printf("Hello world!\n"); }
}
