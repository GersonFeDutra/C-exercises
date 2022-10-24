#include <stdio.h>

#define TABINC 8
#define TRUE 1
#define FALSE 0


/* Entab:
 * Replaces strings of blanks by the minimun number of tabs and blanks to achieve the same
 * spacing. Use the same tab stops as for detab. When either a tab or a single blank would
 * suffice to reach a tab stop, which should be given preference?
 */
int main()
{
	char c;
	int i, occupied, spaces;
	occupied = spaces = 0;

	while ((c = getchar()) != EOF) {

		if (c == ' ')
			++spaces;
		else {
			if (spaces > 0) {
				int cache, tabbed = FALSE;
				i = occupied + spaces;

				while ((cache = i - TABINC) >= 0) { // WATCH
					i = cache;
					printf("\t");
					tabbed = TRUE;
				}
				if (tabbed)
					++i;

				for (i -= occupied; i > 0; --i)
					printf("#");

				spaces = 0;
				occupied = 0;
			}
			else if (c == '\t') {
				occupied = 0;
			}
			else {
				++occupied;

				if (occupied == TABINC)
					occupied = 0;
			}

			printf("%c", c);
		}
	}

	return 0;
}
