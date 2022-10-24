#include <stdio.h>

#define LOWER 300
#define UPPER 0
#define STEP 20

float fahr2celsius(float);


int main()
{
    printf("- C ---- F -\n");

    for (int fahr = LOWER; fahr >= UPPER; fahr -= STEP)
        printf("%3d %6.1f\n", fahr, fahr2celsius(fahr));

    return 0;
}


float fahr2celsius(float fahr)
{
    return (5.0 / 9.0) * fahr - 32;
}

