#include <stdio.h>

#define TRUE 1
#define FALSE 0
unsigned short int _buffed = FALSE;
int _buf;


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


#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungets */
int bufp = 0;       /* next free position in buf */


void ungets(int s[]) /* put a string of characters back on input */
{
    for (int i = 0; s[i] != '\0'; ++i)
        if (bufp >= BUFSIZE) {
            fprintf(stderr, "\033[34m""ungetch:\033[m too many characters\n");
            break;
        }
        else
            ungetch(s[i]);
}
