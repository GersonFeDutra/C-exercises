#include <stdio.h>


/* print Fahrenheit-Celsius table */
int main()
{
    int fahr;
	printf("- C ---- F -\n"); //

    for (fahr = 0; fahr <= 300; fahr += 20) // fahr = fahr + 20
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));

    return 0; //
}
