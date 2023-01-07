#include "calc.h"
#include <stdio.h>
#include <ctype.h>


/* getop: get next operator or numeric operand: pointer version */
int getop(char *s)
{
    /* note that a static variable is initialized only the first time the block is entered */
    static int _buf = '\0';
    int c;

    if (_buf != '\0') {
        c = _buf;    /* rescue buffer */
        _buf = '\0'; /* reset buffer */
    }
    else
        *s = c = getchar();

    while (c == ' ' || c == '\t')
		*s = c = getchar(); /* read blank */

    *(s + 1) = '\0';
	if (!isdigit(c) && c != '.') {
        if (c == '-') {
            /* Check for negative number. */
            if (isdigit(c = getchar()))
                *++s = c;
            else {
                _buf = c;
                return '-';
            }
        }
        else {
            const char ops[][4] = { "SIN", "COS", "TAN", "EXP" };
            for (int o = 0; o < 4; ++o) 
                if (ops[o][0] == c) {
                    /* Read the full word */
                    if ((c = getchar()) == ops[o][1]) {
                        if ((c = getchar()) != ops[o][2])
                            _buf = c;
                    } else
                        _buf = c;

                    return ops[o][0];
                }

            return c; /* not a number */
        }
    }

    while (isdigit(c)) /* collect integer part */
        *++s = c = getchar();

    if (c == '.') /* collect fraction part */
        while (isdigit(*++s = c = getchar()));

    *s = '\0';
    if (c != EOF)
        _buf = c;

    return NUMBER;
}
