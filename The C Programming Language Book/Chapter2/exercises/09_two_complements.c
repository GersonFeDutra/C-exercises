#include <stdio.h>
#include <stdlib.h>


/* bitcount: count 1 bits in x */
int bitcount(int x)
{
    int b;
    for (b = 0; x != 0; x &= (x - 1))
        b++;

    return b;
}


/* In a two's complement number system, x &= (x - 1) deletes the rightmost 1-bit in x.
 * -> This happens because the rightmost bit 1 of the number is always flipped
 * to 0 at his predecessor. For positives the sum always add a bit 1 in the last
 * room if there is zer0s before the rightmost bit 1, else a bit 1 after the
 * last b1t-1 in the sequence, flipping the sequence to 0s. Eg.:
 *      +6_(10) = + 1 1 0 _(2)
 * +6-1=+5_(10) = + 1 0 1 _(2)
 *            & = + 1 0 0
 * and the same goes for negative numbers, except it is reversed:
 *      -6_(10) = - 0 1 0 _(2)
 * -6-1=-7_(10) = - 0 0 1 _(2)
 *            & = - 0 0 0
 * <-- Use this observation to write a faster version of bitcount. */
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
