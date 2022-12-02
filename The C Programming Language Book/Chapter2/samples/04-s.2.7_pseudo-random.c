#include <stdio.h>
#include <stdlib.h>

unsigned long int next = 1;


/* return pseudo-random integer on 0..32767 */
int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}


/* srand: set seed for rand() */
void srand(unsigned int seed)
{
    next = seed;
}


/*
 * Generates pseudo-random numbers. Two integers can be passed as CLI arguments:
 * The first is the seed used to the generation.
 */
int main(int argc, char const *argv[])
{
    int gens = 1;

    if (argc < 2) {
        fprintf(stderr, "\033[33mNo seed provided!\033[m\n");
    }
    else {
        int seed = atoi(argv[1]);
        fprintf(stderr, "\033[32mUsing seed %d.\033[m\n", seed);
        srand(seed);

        if (argc > 2)
            gens = atoi(argv[2]);
    }

    for (int i = 0; i < gens; ++i)
        printf("%d\n", rand());

    return EXIT_SUCCESS;
}
