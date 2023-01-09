#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEF_TAB_INC 8 /* default tab increment */


/* detab: replaces tabs in the input with the proper number of blanks to space
 * to the next tab stop: version 2.
 * accepts tab stop settings as arguments, if none use default. */
int main(int argc, const char *argv[])
{
    char space = ' ';
	int c, occupied = 0, tabinc = DEF_TAB_INC;
	setbuf(stdout, NULL);

    while (--argc)
        if (isdigit(**++argv))
            tabinc = atoi(*argv);
        else if (**argv == '-' && isdigit(*(*argv + 1)))
			occupied = atoi(++*argv);	/* -m: starts at column 'm' */
        else if (**argv == '+' && isdigit(*(*argv + 1)))
			tabinc = atoi(++*argv);	/* +n: tab stop of size 'n' */
        else if (**argv != '\0')
            space = **argv; /* output space character. replace to ease visualize */

	occupied %= tabinc;
	while ((c = getchar()) != EOF) {

        if (c == '\n') {
            occupied = 0;
            putchar(c);
            continue;
        }

		if (c == '\t') {
			for (int i = tabinc - occupied; i > 0; --i)
				putchar(space);
			occupied = 0;
		}
		else {
			occupied = ++occupied % tabinc;
			putchar(c);
		}
	}

	return 0;
}
