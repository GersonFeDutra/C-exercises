/* Binary to integer
 * Converts a string of '0's and '1's (including an optional b or B)
 * into its equivalent integer value. Ignores leading zeros accordingly.
 */
unsigned bitoi(const char[]);

/* Integer to binary
 * Converts an integer into its binary representation as a string.
 * Does not considers leading zeros and signals.
 */
void atobit(unsigned, char[sizeof(int) * 8]);

/* Converts a string of decimal digits into its equivalent integer value. */
int atoi(const char[]);

/* Octal to Integer
 * Converts a string of octal digits (including an optional o, O, or 0)
 * into its equivalent integer value.
 * Does not considers leading zeros and signals.
 */
int octoi(const char[]);

/* Hexadecimal to Integer
 * Converts a string of hexadecimal digits (including an optional 0x or 0X)
 * into its equivalent integer value.
 * Does not considers leading zeros and signals.
 */
int htoi(const char []);

#ifndef SCONVERT
#define SCONVERT
#include <stdio.h>


/* Converts an integer from various formats to integer. */
int sconvert(const char s[]) {
	switch (s[0]) {
		case 'b':
		case 'B':
            return bitoi(s);
            break;
		case 'o':
		case 'O':
            return octoi(s);
            break;
		case '0':
			return (s[1] == 'x' || s[1] == 'X') ? htoi(s) : octoi(s);
			break;
		default:
            return atoi(s);
	}
}


/* Prints an integer in various formats. */
void pr_int(int d)
{
    char bin[sizeof(int) * 8];
    atobit(d, bin);

    printf("%ee 0x%x o%o %d ", d, d, d, d);
	printf("b%s\n", bin);
}


#endif
