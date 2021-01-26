#include <stdio.h>

#define TABINC 8

/* detab: replaces tabs in the input with the proper number of blanks to space to the next tab stop.
Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter? */

int main()
{
	char c;
	int i, occupied = 0;

	while ((c = getchar()) != EOF) {

		if (c == '\t') {

			for (i = 0; i < (TABINC - occupied); ++i) {
				printf("#");
			}
			occupied = 0;
		}
		else {
			++occupied;

			if (occupied == TABINC)
				occupied = 0;

			printf("%c", c);
		}
	}

	return 0;
}
