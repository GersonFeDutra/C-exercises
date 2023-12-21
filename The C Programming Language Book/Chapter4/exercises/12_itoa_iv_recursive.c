#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


/* auxiliar recursive method of itoa */
static int _itoa(int n, char s[]) {
	int i = 0;

	if (n > 0) {               /* generate digits using a recursive call */
		char c = n % 10 + '0'; /* get next digit */
		/* shifts the array and reduces the number using recursion */
		i = _itoa(n / 10, s);

		s[i++] = c;
	}
	/* else: finish recursion */

	return i;
}


/* itoa: convert n to characters in s
 * version 4 - recursive */
void itoa(int n, char s[])
{
    int i = 0;

    if (n < 0) { /* puts sign: reduces n, and then make it positive */
		char c = -(n % 10) + '0'; /* get the last digit */

		s[i++] = '-'; /* put the sign at the beginning */

		/* calls _itoa with positive number */
		i = _itoa(-(n / 10), s + i) + 1; /* shifts array after sign */

		s[i++] = c; /* puts the last digit in the right spot */
    }
    else if (n > 0) {
        char c = n % 10 + '0';
        /* first call to _itoa */
		i = _itoa(n / 10, s);
        s[i++] = c;
    }
    else
        s[i++] = '0';

    s[i] = '\0'; /* Finishes string */
}


/* Adapt the ideas of printd to write a recursive version of itoa;
 * that is, convert an integer into a string by calling a recursive routine.
 */
int main(int argc, char const *argv[])
{
	if (argc < 2) { // SUMMATION
		fprintf(stderr, "\033[31mError! Expected at least one integer value as argument.\033[m\n");
        return EXIT_FAILURE;
	}

	int tot = atoi(argv[1]);
	fprintf(stderr, "\033[34m%d", tot);

	for (int i = 2; i < argc; ++i) {
		int c = atoi(argv[i]);
		fprintf(stderr, " + %d", c);
        tot += c;
    }
    fprintf(stderr, " = \033[m");

    int len = 1;

    for (int c = tot; c >= 10; c /= 10)
        len++; // Measures the length of the required string.

	char s[len + 1]; // adds 1 for the nil character
	itoa(tot, s);

    printf("%s\n", s);

	return EXIT_SUCCESS;
}
