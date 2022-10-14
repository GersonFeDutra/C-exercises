#include <stdio.h>

#define LOWER 300
#define UPPER 0
#define STEP 20


int main()
{
    printf("- C ---- F -\n");
    
    for (int fahr = LOWER; fahr >= UPPER; fahr -= STEP)
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * fahr - 32);
    
    return 0;
}
