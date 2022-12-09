#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]);


/* itoa: convert n to characters in s */
void itoa(int n, char s[])
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

    s[i] = '\0';
    reverse(s);
}


/* In a two's complement number representation, our version of itoa does not
 * handle the larger negative number, that is, the value of n equal to
 * -[2^(wordsize-1)]. Explain why not. Modify it to print that value correctly
 * regardless of the machine in which it runs.
 *
 * Answer:
 * In the old version of itoa, in the statement above:
    if ((sign = n) < 0) // record sign
        n = -n;         // make n positive
 * when n = -[2^(wordsize-1)], -n will try to get the equivalent opposite value
 * but, in two complement number system, MIN = -MAX-1. In other words, the opposite
 * value of a limit is one step more distant in this number system.
 * The possibles solutions may be: to use a higher integer type, or to reduce n once,
 * as shown below:
    if ((sign = n) < 0) { // record sign
        // reduces the value of n, and then make it positive
        s[i++] = -(n % 10) + '0';
        n = -(n / 10);
    }
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

    // Tests the limits
    /*
    char t[sizeof(int) * 8 + 1];
    void itoa_old(int n, char s[]);

    itoa_old(INT_MIN, t);
    printf("%s\n", t);

    itoa(INT_MIN, t);
    printf("%s\n", t);
    */

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

/* itoa: convert n to characters in s */
/*
void itoa_old(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0) // record sign
        n = -n;         // make n positive

    i = 0;
    do { // generate digits in reverse order
        s[i++] = n % 10 + '0'; // get next digit
    } while ((n /= 10) > 0);   // delete it

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}
*/
