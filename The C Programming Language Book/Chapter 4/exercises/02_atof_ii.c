#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/* atof: convert string s to double: version 2 */
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

    if (s[i] == 'e' || s[i] == 'E') {
        i++;

        double mul = 1.0 / 10.0; // `+` reduz power, pois ele é usado como dividendo.
        if (s[i] == '-') 
            mul = 10.0;
        else if (s[i] != '+')
            i--; // Anula o avanço de sinal abaixo.

        i++;
        for (int exp = atoi(s + i); exp > 0; exp--)
            power *= mul;
    }

    return sign * val / power;
}


/* Extend atof to handle scientific notation of the form 123.45e-6,
 * where a floating-pointing number may be followed by e or E and an optionally signed exponent */
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
