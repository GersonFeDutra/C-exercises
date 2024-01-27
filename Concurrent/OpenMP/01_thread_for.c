#include <omp.h>
#include <stdio.h>

int main(void) {
  int i;
#pragma omp parallel num_threads(4)
{
#pragma omp for
    for (i = 0; i <= 100; i++)
      printf("Thread %d run iteration %d from for\n", omp_get_thread_num(), i);
}
}
