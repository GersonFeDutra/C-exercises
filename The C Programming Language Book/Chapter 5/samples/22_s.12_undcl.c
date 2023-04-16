#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int  gettoken(void);

int  tokentype;          /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc */
char out[1000];          /* output string */


/* undcl: convert word description like "x is a function returning a pointer to
 * an array of pointers to functions returning char" which we wll express as
 * `x () * [] * ()` to a declaration, like `char (*(*x())[])() */
int main(void) 
{
    int type;
    char tmp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token); /* is the datatype */

        while ((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                sprintf(tmp, "(*%s)", out);
                strcpy(out, tmp);
            }
            else if (type == NAME) {
                sprintf(tmp, "%s %s", token, out);
                strcpy(out, tmp);
            }
            else
                fprintf(stderr, "\033[31m""Error: Invalid input at %s\033[m\n", token);

        printf("%s\n", out);
    }

    return EXIT_SUCCESS;
}


int gettoken(void)  /* return next token */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t');
        /* skip blanks */

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");

            return tokentype = PARENS;
        }
        else {
            ungetch(c);

            return tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; (*p++ = c = getch()) != ']'; ) /* read indexing */
            if (c == EOF) {
                ungetch(c);
                break;
            }
        *p = '\0';

        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);

        return tokentype = NAME;
    }
    else
        return tokentype = c;
}


/* dcl: parse a declarator */
void dcl(void)
{
    int ns = 0;

    while (gettoken() == '*') /* cont *'s */
        ns++;
    dirdcl();

    while (ns-- > 0)
        strcat(out, " pointer to");
}


/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;

    if (tokentype == '(') {     /* ( dcl ) */
        dcl();

        if (tokentype != ')')
            fprintf(stderr, "\033[31m""Error: missing )\033[m\n");
    }
    else if (tokentype == NAME) /* variable name */
        strcpy(name, token);
    else
        fprintf(stderr, "\033[31m""Error: expected name or (dcl)\033[m\n");

    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}


#define TRUE 1
#define FALSE 0

static char buf; /* buffer for ungetch */
static unsigned short buffed = FALSE; /* next free position in buf */


int getch(void) /* get a (possibly pushed back) character */
{
    if (buffed) {
        buffed = FALSE;
        return buf;
    }
    return getchar();
}


void ungetch(int c) /* push character back on input */
{
    buffed = TRUE;
    buf = c;
}
