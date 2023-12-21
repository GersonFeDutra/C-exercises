#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/* atof: convert string s to double: pointer version */
double atof_(const char *s)
{
    double val, power;
    int sign;

    while (isspace(*s))
        s++; /* skip white space */

    sign = (*s == '-') ? -1 : 1;

    if (*s == '+' || *s == '-')
        s++;

    for (val = 0.0; isdigit(*s); s++)
        val = 10.0 * val + (*s - '0');

    if (*s == '.')
        s++;

    for (power = 1.0; isdigit(*s); s++) {
        val = 10.0 * val + (*s - '0');
        power *= 10.0;
    }

    if (*s == 'e' || *s == 'E') {
        s++;

        double mul = 1.0 / 10.0; // `+` reduz power, pois ele é usado como dividendo.
        if (*s == '-') 
            mul = 10.0;
        else if (*s != '+')
            s--; // Anula o avanço de sinal abaixo.

        s++;
        for (int exp = atoi(s); exp > 0; exp--)
            power *= mul;
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
