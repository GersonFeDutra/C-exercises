#include <stdio.h>


int main()
{
    int lower = 0, upper = 100, step = 10;
    float fahr, celsius = lower;
    
    printf("- C ---- F -\n");

    while (celsius <= upper) {
        fahr = (celsius + 32) / (5.0 / 9.0);
        printf("%5.1f %4.0f\n", celsius, fahr);
        celsius += step;
    }

    return 0;
}
