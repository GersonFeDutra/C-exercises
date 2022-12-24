#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <math.h>

#define MAXOF   100 /* max size of operand or operator */
#define NUMBER '0' /* Signal that a number was found */

int getop(char []);

/* Stack */
void push(double);
double pop(void);

void st_print(void);
void st_dupl(void);
void st_swap(void);
void st_clear(void);

void save(int c);
int access(int c);


/* reverse Polish calculator
 * Add commands for handling variables.
 * (It's easy to provide twenty-six variables with single-letter names)
 * Add a variable for the most recently printed value. */
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


#define MAXVAL 100  /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* values of stack */

/* Variables used in the calculator. */
double pr_var, vars['z' - 'a' + 1];


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
        fprintf(stderr, "\033[31mError: Stack empty. Can not pop.\033[m\n");
        return 0.0;
    }
}


/* st_print: print the top element of the stack, without popping */
void st_print(void)
{
    if (sp > 0) {
        printf("[%g] ", val[sp - 1]);
        pr_var = val[sp - 1];
    } else
        fprintf(stderr, "\033[31mError: Stack empty. Can not print.\033[m\n");
}


/* st_dupl: duplicate the top element of the stack */
void st_dupl(void)
{
    if (sp > 0)
        push(val[sp - 1]);
    else
        fprintf(stderr, "\033[31mError: Stack empty. Can not duplicate.\033[m\n");
}


/* st_swap: swap the two top elements of the stack */
void st_swap(void)
{
    if (sp >= 1) {
        double tmp = val[sp - 1];
        val[sp - 1] = val[sp - 2], val[sp - 2] = tmp; /* swap */
    }
    else
        fprintf(stderr, "\033[31mError: Stack has not enough elements to swap.\033[m\n");
}


/* st_clear: clear the stack */
void st_clear(void)
{
    sp = 0;
}


/* save: save the top value of the stack to a variable `c` */
void save(int c)
{
	if (c >= 'a' && c <= 'z') {
        if (sp > 0)
			vars['z' - c] = val[sp - 1];
		else
            fprintf(stderr, "\033[31mError: Stack empty. Can not save.\033[m\n");
	}
    else
		fprintf(stderr, "\033[34mError: No variable set.\033[m\n");
}


/* access: access a variable `c`, pushing it to the top of stack.
 * Return 0 if c is not between a-z */
int access(int c)
{
	if (c >= 'a' && c <= 'z')
		push(vars['z' - c]);
    else if (c == '_')
        push(pr_var);
    else
        return 0;
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
