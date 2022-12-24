#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


/* atoi: convert s to integer: version 3 */
int atoi(const char s[])
{
    double atof_(const char s[]);

	return (int) atof(s);
}


/* Sum integers passed as arguments to the program. */
int main(int argc, char const *argv[])
{
	if (argc < 3) {
		fprintf(stderr,
			"\033[31mNot enough command line argument. Expects at least one number.\033[m\n");
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


/* atof: convert string s to double */
double atof_(const char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++); /* skip white space */

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    return sign * val / power;
}
