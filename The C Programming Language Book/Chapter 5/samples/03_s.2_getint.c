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
    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;
    if (c != EOF)
        ungetch(c);

    return c;
}


#define SIZE 255 /* size of integer buffer */
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


#define TRUE 1
#define FALSE 0

static unsigned short int _buffed = FALSE;
static int _buf;


/* get a (possibly pushed back) character. */
int getch(void)
{
    if (_buffed) {
        _buffed = FALSE;
        return _buf;
    }

    return getchar();
}


/* Push character back on input.
 * Assumes only one character will be pushed back */
void ungetch(int c)
{
    _buffed = TRUE;
    _buf = c;
}
