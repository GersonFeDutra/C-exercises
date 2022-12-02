#include <stdio.h>
#include <stdlib.h>


/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;

    return b;
}


int main(int argc, char const *argv[])
{

	if (argc < 2) {
		fprintf(stderr,
                "\033[31mError! Expected at least one binary as arguments.\n"
                "binary must be at integer form (unsigned).\033[m\n");
		return EXIT_FAILURE;
	}

    for (int i = 1; i < argc; ++i)
        printf("%u\n", bitcount(atoi(argv[i])));

	return EXIT_SUCCESS;
}
