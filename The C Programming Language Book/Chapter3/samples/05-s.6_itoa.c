#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[]);


/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */

    i = 0;
    do { /* generate digits in reverse order */
        s[i++] = n % 10 + '0'; /* get next digit */
    } while ((n /= 10) > 0);   /* delete it */

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}


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


/* reverse: reverse string s in place */
void reverse(char s[])
{
	char c;
	int i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c; // reverse operation as a single expression.
}
