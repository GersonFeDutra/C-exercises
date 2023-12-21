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

    while (--argc)
        if (isdigit(**++argv))
            tabinc = atoi(*argv);
        else if (**argv == '-' && isdigit(*(*argv + 1)))
            fprintf(stderr, "\033[33m""Warning: Negative number not allowed!\033[m\n");
        else if (**argv != '\0')
            space = **argv;

	while ((c = getchar()) != EOF) {

        if (c == '\n') {
            occupied = 0;
            putchar(c);
            continue;
        }

		if (c == '\t') {
			for (int i = 0; i < (tabinc - occupied); ++i)
				putchar(space);

			occupied = 0;
		}
		else {
			++occupied;

			if (occupied == tabinc)
				occupied = 0;

			putchar(c);
		}
	}

	return 0;
}
