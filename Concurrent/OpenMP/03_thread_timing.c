#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void task1(int n) {
	int i;

	for (i = 0; i < n; i++)
		printf("(%d) - %d\n", omp_get_thread_num(), i);
}

void task2(int a, int b) {
	printf("(%d) - %d\n", omp_get_thread_num(), a + b);
}


int main(void) {
#pragma omp parallel
{
	#pragma omp sections
	{
        #pragma omp section
        {
            double start = omp_get_wtime();
            task1(10);
            double end = omp_get_wtime();
            printf("%f\n", end - start);
        }
        #pragma omp section
        {
            double start = omp_get_wtime();
            task2(20, 30);
            double end = omp_get_wtime();
            printf("%f\n", end - start);
        }
	}
}
}
