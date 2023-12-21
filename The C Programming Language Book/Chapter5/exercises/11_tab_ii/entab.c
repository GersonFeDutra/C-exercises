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
	int c, i, occupied, spaces, tabinc = DEF_TAB_INC;
	occupied = spaces = 0;

    while (--argc)
        if (isdigit(**++argv))
            tabinc = atoi(*argv);
        else if (**argv == '-' && isdigit(*(*argv + 1)))
            fprintf(stderr, "\033[33m""Warning: Negative number not allowed!\033[m\n");
        else if (**argv != '\0')
            tab = **argv;

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
				if (++occupied == tabinc)
					occupied = 0;

			putchar(c);
		}
	}

	return 0;
}
