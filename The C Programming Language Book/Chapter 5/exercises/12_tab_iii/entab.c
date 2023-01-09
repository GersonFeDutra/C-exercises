#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEF_TAB_INC 8
#define TRUE 1
#define FALSE 0


/* entab: replaces strings of blanks by the minimum number of tabs and blanks to
 * achieve the same spacing.
 * accepts tab stop settings as arguments, if none use default. */
int main(int argc, const char *argv[])
{
	char tab = '\t';
	int c, i, m, n, occupied, spaces, tabinc = DEF_TAB_INC;
	occupied = spaces = 0;

    while (--argc)
        if (isdigit(**++argv))
            tabinc = atoi(*argv);
        else if (**argv == '-' && isdigit(*(*argv + 1)))
			occupied = atoi(++*argv);	/* -m: starts at column 'm' */
		else if (**argv == '+' && isdigit(*(*argv + 1)))
			tabinc = atoi(++*argv);	/* +n: tab stop of size 'n' */
        else if (**argv != '\0')
            tab = **argv; /* output tab character. replace to ease visualize */

	occupied %= tabinc;
	while ((c = getchar()) != EOF) {

		if (c == ' ')
			++spaces;
		else {
			if (spaces > 0) {
				int cache, tabbed = FALSE;
				i = occupied + spaces;

				while ((cache = i - tabinc) >= 0) {
					i = cache;
					putchar(tab);
					tabbed = TRUE;
				}
				if (tabbed)
					++i;

				for (i -= occupied; i > 0; --i)
					putchar(' ');

				spaces = 0;
				occupied = 0;
			}
			else if (c == '\t')
				occupied = 0;
			else
				occupied = ++occupied % tabinc;

			putchar(c);
		}
	}

	return 0;
}
