#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int minscanf(char *, ...);

/* Write a private version of scanf analogous to minprintf from the previous section. */
int main(void)
{
    char s[250];
    minscanf("%s", s); // unhandled errors
    printf("Hello, %s!\n", "World");

    double result;
    int a, b;
    char c;
    if (minscanf("%d %c %d", &a, &c, &b) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    switch (c) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = (double)a / b;
            break;
        default: {
            fprintf(stderr, "\033[31m""Illegal operator '%c'!""\033[m\n", c);
            exit(EXIT_FAILURE);
        } break;
    }
    printf("%d %c %d = %g\n", a, c, b, result);

    return EXIT_SUCCESS;
}



#include <stdarg.h>

/** minscanf: minimal scanf with variable argument list.
 * Write a private version of scanf analogous to minprintf from the previous section.
 **/
int minscanf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    char *p;
    union {
        char *c, *s;
        int *i;
        double *d;
    } ptr;

    va_start(ap, fmt); /* make ap point to 1st unamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            int c = getc(stdin);

            if (c != *p) {
                fprintf(stderr, "\033[31m""Format specifier does not match!""\033[m\n");
                ungetc(c, stdin);
                return EXIT_FAILURE;
            }
            else
                continue;
        }
        switch (*++p)
        {
            case 'c': {
                ptr.c = va_arg(ap, char*);
                *ptr.c = getc(stdin);
                break;
            } break;

            case 'd': {
                ptr.i = va_arg(ap, int*);
                *ptr.i = 0;

                int c;
                while ((c = getc(stdin)) >= '0' && c <= '9') {
                    *ptr.i *= 10;
                    *ptr.i += c - '0';
                }
                ungetc(c, stdin);
            } break;

            case 'f': {
                ptr.d = va_arg(ap, double*);
                *ptr.d = 0.0;

                int c;
                while ((c = getc(stdin)) >= '0' && c <= '9') {
                    *ptr.d *= 10;
                    *ptr.d += c - '0';
                }
                if (c == '.') {
                    double frac = 0.0;
                    size_t precision = 0;
                    while ((c = getc(stdin)) >= '0' && c <= '9') {
                        frac *= 10;
                        frac += c - '0';
                        ++precision;
                    }
                    if (precision > 0)
                        frac /= pow(10, precision);
                    *ptr.d += frac;
                }
                ungetc(c, stdin);
            } break;

            case 's': {
                ptr.s = va_arg(ap, char*);

                for (*ptr.s = getc(stdin); *ptr.s != '\n' && *ptr.s != EOF; *ptr.s = getc(stdin))
                    ++ptr.s;
                *ptr.s = '\0';
            } break;

            default:
                fprintf(stderr, "\033[31m""Illegal format specifier!""\033[m\n");
                break;
        }
        va_end(ap); /* clean up when done */
    }
    return EXIT_SUCCESS;
}
