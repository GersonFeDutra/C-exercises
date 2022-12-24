#include <stdio.h>

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
