#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


/* atoi: convert s to integer: version 2 */
int atoi(const char s[])
{
	int i, n, sign;

    for (i = 0; isspace(s[i]); i++); /* skip white space */

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') /* skip sign */
        i++;

	for (n = 0; isdigit(s[i]); i++) /* convert integer part */
		n = 10 * n + (s[i] - '0');

	return sign * n;
}


/* Sum integers passed as arguments to the program. */
int main(int argc, char const *argv[])
{
	if (argc < 3) {
		fprintf(stderr,
			"\033[31mNot enough command line argument. Expects at least two integers.\033[m\n");
		return EXIT_FAILURE;
	}

	int t = atoi(argv[1]);
	fprintf(stderr, "\033[34m%d", t);

	for (int i = 2; i < argc; ++i) {
		int x = atoi(argv[i]);
		t += x;
		fprintf(stderr, " + %d", x);
	}

	fprintf(stderr, " = \033[m");
	printf("%d\n", t);

	return EXIT_SUCCESS;
}
