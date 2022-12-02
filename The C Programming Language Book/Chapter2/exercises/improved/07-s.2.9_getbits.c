#include "sconvert.h"
#include <stdio.h>
#include <stdlib.h>


/* get_bits: get n bits from position p */
unsigned get_bits(unsigned x, int p, int n)
{
    // Note que se n + 1 > p: o retorno será Zer0:
    // Ex. p = 3, n = 5:
    //                           p
    // 11 10  9  8 , 7  6  5  4  3  2  1  0
    //  1  1  0  0 , 1  1  0  0  1  0  1  0
    //                        n:[|  |  |  |  |
    // Ex2. p = 3, n = 4:
    //                           p
    // 11 10  9  8 , 7  6  5  4  3  2  1  0
    //  1  1  0  0 , 1  1  0  0  1  0  1  0
    //                        n:[|  |  |  |]
    return (x >> (p + 1 - n)) & ~(~0 << n);
}


int main(int argc, char const *argv[])
{
	if (argc != 4) {
		fprintf(stderr,
				"\033[31mError! Expected three integers as arguments:\n"
				"(x=binary at int, (16), bit (b10000), octal (o100) or hex (0x10) form,"
				"p=bit position from lsb, n=number of bits) [n + 1 <= p]\033[m\n");
		return EXIT_FAILURE;
	}

	pr_int(get_bits(sconvert(argv[1]), atoi(argv[2]), atoi(argv[3])));

	return EXIT_SUCCESS;
}
