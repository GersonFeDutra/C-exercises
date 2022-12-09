#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BASE ('z' - 'a' + 1) + 10 /* Max number-base representable in simple characters. */
/* To N-Base Character: converts an integer to a n-base character representation symbol. */
#define TO_NBASE_C(FROM) FROM < 10 ? FROM + '0' : FROM - 10 + 'a'
void reverse(char s[]);



/* itob: converts the integer n into a base b character representation in the string s.
 * Assumes b >= 2. */
void itob(int n, char s[], unsigned char b)
{
    int i = 0, sign;

    if ((sign = n) < 0) { /* record sign */
        /* reduces the value of n, and then make it positive */
        s[i++] = TO_NBASE_C(-(n % b));
        n = -(n / b);
    }
    else {
        /* reduces the value of n once */
        s[i++] = TO_NBASE_C(n % b);
        n /= b;
    }

    while (n > 0) {  /* generate digits in reverse order */
        s[i++] = TO_NBASE_C(n % b); /* get next digit */
        n /= b; /* delete it */
    }

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    reverse(s);
}


/* Write the function itob(n,s,b) */
int main(int argc, char const *argv[])
{
    int b;
    if (argc != 3 || (b = atoi(argv[2])) < 2 || b > MAX_BASE) {
        fprintf(stderr, "\033[31mError! Expected two integer arguments: "
                "a decimal integer, and an integer base (2-%d).\033[m\n", MAX_BASE);
        return EXIT_FAILURE;
    }

    char s[sizeof(int) * 8 + 1];
    itob(atoi(argv[1]), s, b);

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
