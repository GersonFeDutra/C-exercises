#include "calc.h"
#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <math.h>


/* reverse Polish calculator: multiple source files version. */
int main(void)
{
    int type;
    double op2;
	char s[MAXOF];

	while ((type = getop(s)) != EOF)
        switch (type) {
            case NUMBER: push(atof(s)); break;
            case '+':    push(pop() + pop()); break;
            case '*':    push(pop() * pop()); break;
            case '-': {
                op2 = pop();
                push(pop() - op2);
            } break;
            case '/': {
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    fprintf(stderr, "\033[31mError: Zero division\033[m\n");
            } break;
            case '%': {
                op2 = pop();
                double op1 = pop();

                if (op2 != 0.0) {
                    /* Convert to int to trim the value. */
                    int op1d = (int) op1;
                    int op2d = (int) op2;

                    if ((double) op1d != op1 || (double) op2d != op2)
                        /* Check if the number has a decimal place value */
                        fprintf(stderr,
                                "\033[33mWarning: Real number trimmed to integer"
                                "at modulus operation.\033[33m\n");
                    push(op1d % op2d);
                }
                else
                    fprintf(stderr, "\033[31mError: Zero division\033[m\n");
            } break;
            case '^': {
                op2 = pop();
                push(pow(pop(), op2));
            } break;
            case '\n': printf("\t%.8g\n", pop()); break;
            case 'S': push(sin(pop())); break;
            case 'C': push(cos(pop())); break;
            case 'T': push(tan(pop())); break;
            case 'E': push(exp(pop())); break;
            case 'P':  st_print(); break;
            case 'D':  st_dupl();  break;
            case 'R':  st_swap();  break;
            case 'K':  st_clear(); break;
            case '#': {
                /* Ignores line, and print splitter if empty line */
                int c;
                st_clear();
                while ((c = getchar()) == ' ' || c == '\t'); /* Ignores blank */

                if (c == EOF || c == '\n')
                    fprintf(stderr, "\033[34m--------\033[m\n");
                else
                    while ((c = getchar()) != EOF && c != '\n'); /* Read to next line */

                if (c == EOF)
                    return EXIT_SUCCESS;
            } break;
            case '=': {
                int c;
                while ((c = getchar()) == ' ' || c == '\t'); /* Ignores blank */

                if (c == EOF)
                    return EXIT_SUCCESS;
                else
                    save(c);
            } break;
            default: {
                if (!access(type))
                    fprintf(stderr, "\033[31mError: Unknown command %s\033[m\n", s);
            } break;
        }

    return EXIT_SUCCESS;
}
