#include <stdio.h>

/* print Fahrenheit-Celsius table
     for fahr = 0, 20, ..., 300 */
int main()
{
    int lower = 0, upper = 300, step = 20;
    float fahr = lower, celsius; // using float for decimal precision

    printf("- F ---- C -\n");

    while (fahr <= upper) {
        // We need to assure that the division is not truncated
        // (because of the integer division property), we can do this as shown above:
        //celsius = 5 * (fahr - 32) / 9; // product first
        //celsius = 5.0 / 9.0 * (fahr - 32); // explicit decimal
        //celsius = 5 / 9.0 * (fahr - 32); // half explicit decimal (5 will be converted to float)
        celsius = 5. / 9. * (fahr - 32); // explicit decimal (no decimal places)

        printf("%3.0f %6.1f\n", fahr, celsius); // formated output
        fahr += step;
    }

    return 0;
}
