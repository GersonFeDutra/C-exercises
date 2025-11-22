#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void minprintf(char *, ...);

int main(void)
{
    minprintf("Hello, %s!\n", "World");
    minprintf("%<3d %=3c %>3d = %>3.3f\n", 1, '/', 4, 1.0 / 4);

    return EXIT_SUCCESS;
}



#include <stdarg.h>

/** minprintf: minimal printf with variable argument list
 * Revise minprintf to handle more of the other facilities of printf.
 * 
 * @param fmt: format string
 * @note Usage: %[X][N][.P]Y where X is alignment, N is width, P is precision:
 * [V] are optional V values
 * X can be <, > or = where: < is left alignment, > is right alignment, and = is center alignment
 * Y can be d, f, s, c where: d is decimal, f is floating point, s is string, and c is character
 * N is the width, and P is the precision (in decimal digits)
 **/
void minprintf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    char *p;
    union {
        char *sval;
        int ival;
        double dval;
    } arg;

    va_start(ap, fmt); /* make ap point to 1st unamed arg */
    for (p = fmt; *p; p++) {
        #pragma region Skip non-format specifier characters
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        #pragma endregion

        #pragma region Capture alignment
        enum { LEFT, CENTER, RIGHT } alignment = LEFT;
        switch (*++p) {
            case '<':
                alignment = LEFT;
                break;
            case '>':
                alignment = RIGHT;
                break;
            case '=':
                alignment = CENTER;
                break;
            default:
                --p;
                break;
        }
        #pragma endregion

        #pragma region Capture width
        size_t width = 0;
        while (*++p >= '0' && *p <= '9') {
            width *= 10;
            width += *p - '0';
        }
        #pragma endregion

        #pragma region Capture precision
        long precision = -1;
        if (*p == '.') {
            precision = 0;
            while (*++p >= '0' && *p <= '9') {
                precision *= 10;
                precision += *p - '0';
            }
        }
        #pragma endregion

        #pragma region Capture type
        switch (*p)
        {
            case 'c':
                arg.ival = va_arg(ap, int);
                putchar(arg.ival);
                break;

            case 'd':
                arg.ival = va_arg(ap, int);
                if (arg.ival < 0) {
                    putchar('-');
                    arg.ival = -arg.ival;
                    --width;
                }

                // numeric approach: cpu intensive task, can be replaced by a simple stack.
                unsigned places = log10(arg.ival);
                long decimal_power = powl(10, places);

                if (places < width) {
                    #pragma region Left padding
                    switch (alignment) {
                        case RIGHT:
                            for (unsigned i = 0; i < width - places; ++i)
                                putchar(' ');
                            break;
                        case CENTER:
                            for (unsigned i = 0; i < (width - places) / 2; ++i)
                                putchar(' ');
                            break;
                        default:
                            break;
                    }
                    #pragma endregion
                }

                while (decimal_power >= 1) {
                    putchar('0' + arg.ival / decimal_power);
                    arg.ival %= decimal_power;
                    decimal_power /= 10;
                }

                if (places < width) {
                    #pragma region Right padding
                    switch (alignment) {
                        case LEFT:
                            for (unsigned i = 0; i < width - places; ++i)
                                putchar(' ');
                            break;
                        case CENTER:
                            for (unsigned i = 0; i < (width - places) / 2; ++i)
                                putchar(' ');
                            break;
                        default:
                            break;
                    }
                    #pragma endregion
                }
                break;

            case 'f': {
                arg.dval = va_arg(ap, double);
                if (arg.ival < 0) {
                    putchar('-');
                    arg.ival = -arg.ival;
                    --width;
                }
                if (precision > -1) {
                    // numeric approach: cpu intensive task, can be replaced by a simple stack.
                    // double values may have larger magnitude than long values
                    long long integer = round(arg.dval);
                    long long decimal_power = pow(10, log10(integer));
                    arg.dval -= integer; // remove integer part

                    if (precision + (arg.dval != 0) < width)
                        width -= precision + (arg.dval != 0); // - decimal places and dot (.)
                    else
                        width = 0;

                    long long places = integer > 0 ? log10(integer) : 0;

                    if (places < width) {
                        #pragma region Left padding
                        switch (alignment) {
                            case RIGHT:
                                for (unsigned i = 0; i < width - places; ++i)
                                    putchar(' ');
                                break;
                            case CENTER:
                                for (unsigned i = 0; i < (width - places) / 2; ++i)
                                    putchar(' ');
                                break;
                            default:
                                break;
                        }
                        #pragma endregion
                    }

                    while (integer >= 1) {
                        putchar('0' + integer / decimal_power);
                        integer %= decimal_power;
                        decimal_power /= 10;
                    }
                    if (arg.dval != 0)
                        putchar('.');

                    while (precision-- != 0) {
                        arg.dval *= 10;
                        putchar((int)(arg.dval) + '0');
                        arg.dval -= (int)(arg.dval);
                    }

                    if (places < width) {
                        #pragma region Right padding
                        switch (alignment) {
                            case LEFT:
                                for (unsigned i = 0; i < width - places; ++i)
                                    putchar(' ');
                                break;
                            case CENTER:
                                for (unsigned i = 0; i < (width - places) / 2; ++i)
                                    putchar(' ');
                                break;
                            default:
                                break;
                        }
                        #pragma endregion
                    }
                }
                else {
                    // fallback: search about %f and %g precision in stdio.h references
                    char str[256];

                    switch (alignment) {
                        case LEFT:
                            printf("%-*f", width, arg.dval);
                            break;
                        case CENTER: {
                            snprintf(str, sizeof(str), "%g", arg.dval);
                            size_t length = strlen(str);
                            if (length < width) {
                                for (unsigned i = 0; i < (width - strlen(str)) / 2; ++i)
                                    putchar(' ');
                                printf("%s", str);
                                for (unsigned i = 0; i < (width - strlen(str)) / 2; ++i)
                                    putchar(' ');
                            }
                        } break;
                        default:
                            printf("%*f", width, arg.dval);
                            break;
                    }
                }
            } break;

            case 's': {
                arg.sval = va_arg(ap, char *);
                size_t length = strlen(arg.sval);

                switch (alignment) {
                    case LEFT:
                        printf("%*s", width, arg.sval);
                        break;
                    case CENTER: {
                        if (length < width) {
                            for (unsigned i = 0; i < (width - strlen(arg.sval)) / 2; ++i)
                                putchar(' ');
                            printf("%s", arg.sval);
                            for (unsigned i = 0; i < (width - strlen(arg.sval)) / 2; ++i)
                                putchar(' ');
                        }
                    } break;
                    default:
                        printf("%*s", width, arg.sval);
                        break;
                }
            } break;

            default:
                putchar(*p);
                break;
        }
        #pragma endregion

        va_end(ap); /* clean up when done */
    }
}
