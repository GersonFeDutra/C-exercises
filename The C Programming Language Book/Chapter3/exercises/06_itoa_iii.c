#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]);


/* itoa: convert n to characters in s, padded to fill a width of w. */
void itoa(int n, char s[], int w)
{
    int i = 0, sign;

    if ((sign = n) < 0) { /* record sign */
        /* reduces the value of n, and then make it positive */
        s[i++] = -(n % 10) + '0';
        n = -(n / 10);
    }
    else {
        /* reduces the value of n once */
        s[i++] = n % 10 + '0';
        n /= 10;
    }

    while (n > 0) {  /* generate digits in reverse order */
        s[i++] = n % 10 + '0'; /* get next digit */
        n /= 10; /* delete it */
    }

    if (sign < 0)
        s[i++] = '-';

    while (i < w)
        s[i++] = ' ';

    s[i] = '\0';
    reverse(s);
}


#define PAD 8
#define HIGHER(A, B) A > B ? A : B
/* Write a version of itoa that accepts three arguments instead of two.
 * The third argument is a minimum field width; the converted number must be padded with blanks on
 * the left if necessary to make it wide enough.
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


/* reverse: reverse string s in place */
void reverse(char s[])
{
	char c;
	int i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c; // reverse operation as a single expression.
}
