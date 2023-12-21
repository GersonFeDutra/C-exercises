#include <stdio.h>
#include <stdlib.h> /* for atof */

#define MAXOF   100 /* max size of operand or operator */
#define NUMBER '0' /* Signal that a number was found */

int getop(char []);
void push(double);
double pop(void);


/* reverse Polish calculator
 * Given the basic framework, it's straightforward to extend the calculator.
 * Add the modulus (%) operator and provisions for negative numbers.
 */
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
            case '\n':   printf("\t%.8g\n", pop()); break;
            default:     fprintf(stderr, "\033[31mError: Unknown command %s\033[m\n", s); break;
        }

    return 0;
}


#define MAXVAL 100  /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* values of stack */


/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        fprintf(stderr, "\033[31mError: Stack full, can't push %g\n");
}


/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        fprintf(stderr, "\033[31mError: Stack empty\033[m\n");
        return 0.0;
    }
}


#include <ctype.h>

int getch(void);
void ungetch(int);

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


#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */


int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        fprintf(stderr, "\033[34m""ungetch:\033[m too many characters\n");
    else
        buf[bufp++] = c;
}
