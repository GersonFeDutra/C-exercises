#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


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


int main(int argc, char const *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "\033[31mWarning! Expected, at least one real number as argument.\033[m\n");

        return EXIT_FAILURE;
    }

    float n = atof_(argv[1]);
    long double sum = n;
    setbuf(stderr, NULL);
    fprintf(stderr, "\033[34m%.3f ", n);

    for (int i = 2; i < argc; ++i) {
        sum += n = atof_(argv[i]);
        fprintf(stderr, "+ %.3f ", n);
    }

    fprintf(stderr, "= \033[m");
    printf("%.4LF\n", sum);

    return EXIT_SUCCESS;
}
