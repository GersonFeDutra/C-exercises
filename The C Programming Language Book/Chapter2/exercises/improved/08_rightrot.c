#include "sconvert.h"
#include <stdio.h>
#include <stdlib.h>


/* Right Rotation
 * Returns the value of the integer x rotated to the right by n bit positions.
 */
int rightrot(int x, int n)
{
	return (x >> n) | (x << (sizeof(int) * 8 - n));
}

/*
unsigned leftrot(int x, int n)
{
	return (x << n) | x >> (sizeof(int) * 8 - n);
}
*/

/* Write the function rightrot(x,p,n). */
int main(int argc, char const *argv[])
{
	if (argc != 3) {
		fprintf(stderr,
				"\033[31mError! Expected two integers as arguments:\n"
				"(x=binary at int, (16), bit (b10000), octal (o100) or hex (0x10) form, "
				"n=number of bits to rotate)\033[m\n");
		return EXIT_FAILURE;
	}

	pr_int(rightrot(sconvert(argv[1]), atoi(argv[2])));

	return EXIT_SUCCESS;
}
