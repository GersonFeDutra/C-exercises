#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int getch(void);
void ungetch(int c);


/* get next integer from input into *pn
 * returns: EOF, 0 = NotANumber, >0: integer found */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()));
        /* skip white space */

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* is not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int s = c;
        if (!isdigit(c = getch())) {
            ungetch(c);
            ungetch(s);
            return 0; /* is not a number */
        }
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;
    if (c != EOF)
        ungetch(c);

    return c;
}


#define SIZE 255 /* size of integer buffer */
/* As written, getint treats a + or - not followed by a digit as a valid representation of zero.
 * Fix it to push such a character back on the input. */
int main(void)
{
    int n, array[SIZE], getint(int *);

    int ret;
    for (n = 0; n < SIZE && (ret = getint(&array[n])) != EOF && ret != 0; n++);
        /* saves the integer inputs into the array */

    void pr_arr(const int arr[], int len);
    pr_arr(array, n);

    return EXIT_SUCCESS;
}


/* prints an array of integers */
void pr_arr(const int arr[], int len)
{
    putchar('[');
    if (len > 0)
        printf("%d", arr[0]);
    for (int i = 1; i < len; ++i)
        printf(", %d", arr[i]);
    printf("]\n");
}


/* we use a buffer of size 2, so we can ungetch the sign with the NAN extra character */
#define BUFSIZE 2

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
