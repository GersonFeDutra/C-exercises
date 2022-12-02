#include <stdio.h>
#include <stdlib.h>


/* Set Bits
 * Returns x with the n bits that begin at position p set to the rightmost n bits of y,
 * leaving the other bits unchanged.
 */
unsigned setbits(int x, int p, int n, int y)
{
	unsigned mask = ~(~0 << (p + 1)) & (~0 << (p + 1 - n));

    return (x | mask) & ( (y & mask) | ~mask );
}


/* Write the function setbits(x,p,n,y). */
int main(int argc, char const *argv[])
{
	void pr_int(int d);

	if (argc != 5) {
		fprintf(stderr,
				"\033[31mError! Expected four integers (binaries must be at int form) "
    			"as arguments:\n(x=target binary, p=bit position from lsb, "
				"n=number of bits, y=source binary) [n + 1 <= p]\033[m\n");
		return EXIT_FAILURE;
	}

	pr_int(setbits(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])));

	return EXIT_SUCCESS;
}

void pr_int(int d)
{
	printf("%ee 0x%x o%o %d\n", d, d, d, d);
}
