#include "calc.h"
#include <stdio.h>
#include <ctype.h>


/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i = 0, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t');
        /* read blank */

    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        if (c == '-') {
            /* Check for negative number. */
            if (isdigit(c = getch()))
                s[++i] = c;
            else {
                ungetch(c);
                return '-';
            }
        }
        else {
            const char ops[][4] = { "SIN", "COS", "TAN", "EXP" };
            for (int o = 0; o < 4; ++o) 
                if (ops[o][0] == c) {
                    /* Read the full word */
                    if ((c = getch()) == ops[o][1]) {
                        if ((c = getch()) != ops[o][2])
                            ungetch(c);
                    } else
                        ungetch(c);

                    return ops[o][0];
                }

            return c; /* not a number */
        }
    }

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()));
            /* collect integer part */

    if (c == '.')
        while (isdigit(s[++i] = c = getch()));
            /* collect fraction part */

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}
