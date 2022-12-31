#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


static int p; /* actual padding on the string s in itoa */


/* auxiliar recursive method of itoa, returns offset */
static int _itoa(int n, char s[], int w, int i) {

	if (n > 0) {               /* generate digits using a recursive call */
		char c = n % 10 + '0'; /* get next digit */
		/* shifts the array and reduces the number using recursion */
		i = _itoa(n / 10, s, w, i + 1);

		s[i++] = c;
	}
    else { /* finish recursion */
        for (p = 0; i < w; i++, p++) /* Add leading padding */
            s[p] = ' ';
        i = p;
    }

	return i;
}


/* itoa: convert n to characters in s, padded to fill a width of w.
 * version 5 - recursive */
void itoa(int n, char s[], int w)
{
    int i = 0;

    if (n < 0) { /* puts sign: reduces n, and then make it positive */
		char c = -(n % 10) + '0'; /* get the last digit */
        p = 0; /* resets p */

		/* calls _itoa with positive number */
		i = _itoa(-(n / 10), s, w - 1, 1); /* reduces width to accommodate sign */
		s[i++] = c; /* puts the last digit in the right spot */

		s[p - 1] = '-'; /* puts the sign at the beginning of the number */
    }
    else if (n > 0) {
        char c = n % 10 + '0';
        /* first call to _itoa */
		i = _itoa(n / 10, s, w, 1);
        s[i++] = c;
    }
    else
        s[i++] = '0';

    s[i] = '\0'; /* Finishes string */
}


#define PAD 8
#define HIGHER(A, B) A > B ? A : B
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

	char s[HIGHER(len, PAD) + 1]; // adds 1 for the nil character
	itoa(tot, s, PAD);

    printf("%s\n", s);

	return EXIT_SUCCESS;
}
