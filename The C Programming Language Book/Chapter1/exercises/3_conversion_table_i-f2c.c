#include <stdio.h>

/* print Fahrenheit-Celsius table
     for fahr = 0, 20, ..., 300 */
int main()
{
    int lower = 0, upper = 300, step = 20;
    float fahr = lower, celsius;

    printf("- F ---- C -\n");

    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr += step;
    }

    return 0;
}
