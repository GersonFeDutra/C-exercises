#include <stdio.h>

#define TABINC 8


/* Detab:
 * Replaces tabs in the input with the proper number of blanks to space to the next tab stop.
 * Assume a fixed set of tab stops, say every n columns.
 * Should n be a variable or a symbolic parameter?
 */
int main()
{
	int c, i, occupied = 0;

	while ((c = getchar()) != EOF) {

        if (c == '\n') {
            occupied = 0;
            putchar(c);
            continue;
        }

		if (c == '\t') {

			for (i = 0; i < (TABINC - occupied); ++i)
				putchar('#'); // replace it with a blank space!

			occupied = 0;
		}
		else {
			++occupied;

			if (occupied == TABINC)
				occupied = 0;

			putchar(c);
		}
	}

	return 0;
}
