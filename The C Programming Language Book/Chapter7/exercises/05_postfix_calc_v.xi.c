#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <string.h>
#include <math.h>

#define MAX    500 /* max size of a line of input */
#define MAXOF  100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

#pragma region Declarations
/* Input */
int getop(char line[], char s[], int pos[1]);
/* Operators */
int get_line(char s[], int lim);

/* Stack */
void push(double);
double pop(void);
// extras
void st_print(void);
void st_dupl(void);
void st_swap(void);
void st_clear(void);
// variables
void save(int c);
int access(int c);
#pragma endregion // Declarations

// TODO
/** reverse Polish calculator: version 11
 * Rewrite the postfix calculator of Chapter 4 to use scanf
 * and/or sscanf to do the input and number conversion.
 **/
int main(void)
{
    int type, pos[1];
    double op2;
    char line[MAX], s[MAXOF];

	while (scanf("%[^\n]", line) > 0) {
        s[0] = getchar();
        s[1] = '\0';
        strcat(line, s);
        pos[0] = 0;
        while ((type = getop(line, s, pos)) != '\0') 
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
                    st_clear();
                    int i;
                    for (i = pos[0]; line[i] == ' ' || line[i] == '\t'; ++i); /* Ignores blank */

					if (line[i] == '\n' || line[i] == '\0')
						fprintf(stderr, "\033[34m--------\033[m\n");

                    line[pos[0]] = '\0'; /* Force go to next line */
                } break;
                case '=': {
                    int i;
                    for (i = pos[0]; line[i] == ' ' || line[i] == '\t'; i++); /* Ignores blank */

                    if (line[i] != '\0') {
                        save(line[i]);
                        pos[0] = i + 1;
                    }
                } break;
                default: {
                    if (!access(type))
                        fprintf(stderr, "\033[31mError: Unknown command %s\033[m\n", s);
                } break;
            }
	}

	return EXIT_SUCCESS;
}


#pragma region Stack
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
#pragma endregion // Stack


#pragma region Operators
#include <ctype.h>


/* getop: get next operator or numeric operand, shifts line when read */
int getop(char line[], char s[], int pos[1])
{
    /* i -> line, j -> s */
    int i, j = 0;

    for (i = pos[0]; (s[0] = line[i]) == ' ' || line[i] == '\t'; i++);
        /* read blank */

    s[1] = '\0';
    if (!isdigit(line[i]) && line[i] != '.') {
        if (line[i] == '\n') {
            s[0] = '\n';
            s[1] = '\0';
            ++pos[0];
            return '\n';
        }
        if (line[i] == '-') {
            /* Check for negative number. */
            if (isdigit(line[i + 1]))
                s[++j] = line[++i];
            else {
                pos[0] = i + 1;
                return '-';
            }
        }
        else {
            const char ops[][4] = { "SIN", "COS", "TAN", "EXP" };
            for (int o = 0; o < 4; ++o)
                if (ops[o][0] == line[i]) {
                    /* Read the full word */
                    if (line[i + 1] == ops[o][1]) {
                        if (line[i + 2] == ops[o][2])
                            i++;
                        i++;
                    }
                    pos[0] = i + 1;
                    return ops[o][0];
                }

            int c = line[i];
            pos[0] = i + 1;
            return c; /* not a number */
        }
    }

    if (isdigit(line[i]))
        while (isdigit(line[i]))
			s[j++] = line[i++]; /* collect integer part */

    if (line[i] == '.') {
        i++;
        while (isdigit(s[++j] = line[i]))
            ++i; /* collect fraction part */
    }

    s[j] = '\0';

    pos[0] = i;
    return NUMBER;
}
#pragma endregion // Operators
