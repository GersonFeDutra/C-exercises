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
	void pr_int(int d);

	if (argc != 3) {
		fprintf(stderr,
				"\033[31mError! Expected two integers as arguments:\n"
				"(x=target binary at int form, n=number of bits to rotate)\033[m\n");
		return EXIT_FAILURE;
	}

	pr_int(rightrot(atoi(argv[1]), atoi(argv[2])));

	return EXIT_SUCCESS;
}


void pr_int(int d)
{
	printf("%ee 0x%x o%o %d\n", d, d, d, d);
}
