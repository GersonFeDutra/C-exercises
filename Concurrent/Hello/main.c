#include <stdio.h>
#include <omp.h>


int main()
{
    #pragma omg parallel
    {
        printf("The parallel region is executed by thread%d\n", omp_get_thread_num());
    }
}
