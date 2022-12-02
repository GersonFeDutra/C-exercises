#include <stdio.h>
#include <stdlib.h>
#include "sconvert.h"


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

	if (argc != 5) {
		fprintf(stderr, 
				"\033[31mError! Expected four integers as arguments:\n"
				"\t* Binaries may be at int (16), bit (b10000), octal (o100) or hex (0x10) form.\n"
				"(x=target binary, p=bit position from lsb, n=number of bits, y=source binary) "
				"[n + 1 <= p]\033[m\n");
		return EXIT_FAILURE;
	}

	unsigned b = setbits(sconvert(argv[1]), atoi(argv[2]), atoi(argv[3]), sconvert(argv[4]));

	pr_int(b);

	return EXIT_SUCCESS;
}
