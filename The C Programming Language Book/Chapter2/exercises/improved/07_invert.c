#include <stdio.h>
#include <stdlib.h>
#include "sconvert.h"


/* Invert
 * Returns x with the n bits that begin at position p inverted (i.e., 1 changed to 1 and vice-versa)
 * leaving the others unchanged.
 */
unsigned invert(int x, int p, int n)
{
	unsigned mask = ~(~0 << (p + 1)) & (~0 << (p + 1 - n));

	return (x | mask) & ( (~x & mask) | ~mask );
}


/* Write the function invert(x,p,n). */
int main(int argc, char const *argv[])
{

	if (argc != 4) {
		fprintf(stderr,
				"\033[31mError! Expected three integers as arguments:\n"
				"(x=target binary at int (16), bit (b10000), octal (o100) or hex (0x10) form, "
				"p=bit position from lsb, n=number of bits) [n + 1 <= p]\033[m\n");
		return EXIT_FAILURE;
	}

	pr_int(invert(sconvert(argv[1]), atoi(argv[2]), atoi(argv[3])));

	return EXIT_SUCCESS;
}
