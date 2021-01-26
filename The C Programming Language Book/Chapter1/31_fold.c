#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MAXLENGTH 100

int add_to_string(char str[], int len, char c, int at);

/* fold: fold long input lines into two or more shorter lines after the last non-blanck characters
that occurs before the n-th column of input. Make sure your program does something intelligent with
very long lines, and if there are no blanks or tabs before the specified column. */

int main()
{
	const int length = MAXLENGTH - 1;
	char c, firstline[MAXLENGTH];
	int i = 0, done = FALSE;

	while ((c = getchar()) != EOF) {

		if (!done) {

			if ((i = add_to_string(firstline, length, c, i)) == MAXLENGTH) {
				done = TRUE;
			}
			else if (c == '\n') {

				if ((c = getchar()) == ' ' || c == '\t') {
					firstline[i - 1] = '\0';
					done = TRUE;
				}
				else {
					if ((i = add_to_string(firstline, length, c, i)) == MAXLENGTH) {
						done = TRUE;
					}
				}
			}
		}

		if (done && (c == '\n') && (c = getchar()) == '\n') {
			printf("%s...\n\n", firstline);
		}
	}

	return 0;
}

/* Add a char into string, limiting length. */
int add_to_string(char str[], int len, char c, int at) {

	if (at >= len) {
		str[at] = '\0';
	}
	else {
		str[at] = c;
	}

	return at + 1;
}
