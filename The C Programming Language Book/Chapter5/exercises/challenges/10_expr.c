#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <math.h>

#define MAX    500 /* max size of a line of input */
#define MAXOF  100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define ERR    EOF /* signal that the arg type is invalid. */

int getop(char arg[]);

/* Stack */
void push(double);
double pop(void);

void st_print(void);
void st_dupl(void);
void st_swap(void);
void st_clear(void);

void save(int c);
int access(int c);


// TODO
/* Reverse Polish calculator: version 10
 * Challenge: accept multiple operand/ operator in a single argument */
int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "\033[33m""Usage: Reverse polish calculator.\033[m\n");
        fprintf(stderr, "\033[33m""Expected expression as argument where each is"
                " an operator or operand.\033[m\n");
        return 0;
    }

    int type;
    double op2;
    while (--argc > 0)
        switch (type = getop(*++argv)) {
            case '\0': break;
            case NUMBER: push(atof(*argv)); break;
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
                                " at modulus operation.\033[33m\n");
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
            case '#': putchar('\n');    break;
            case 'P': st_print(); break;
            case 'D': st_dupl();  break;
            case 'R': st_swap();  break;
            case 'K': st_clear(); break;
            case '=': {
                save(**++argv);
                argc--;
            } break;
            default: {
                if (!access(type))
                    fprintf(stderr, "\033[31mError: Unknown command %s\033[m\n", *argv);
            } break;
        }

    putchar('\n');

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
		fprintf(stderr, "\033[31mError: No variable set.\033[m\n");
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


/* getop: get the type of next operator or numeric operand */
int getop(char arg[])
{
    if (isdigit(*arg) || *arg == '.')
        return NUMBER;

    if (*arg == '-') {
        /* Check for negative number. */
        if (isdigit(*(arg + 1)))
            return NUMBER;
        else
            return '-';
    }

    int c, err;
    err = c = *arg;
    const char ops[][4] = { "SIN", "COS", "TAN", "EXP" };
    for (const char (*o)[4] = ops; **o != '\0'; ++o)
        while (**o != '\0' && *arg != '\0')
            if (*(*o++) != *arg++)
                return err; /* if not reading an ops type, will return the first char */
            else
                err = ERR;  /* assumes reading an ops type: error if no full matched */
    return c; /* not a number */
}
