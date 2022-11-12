#include <stdio.h>

#define MAXLENGTH 100
#define MAX_LINES 3

int get_line_trimmed(char s[], int lim, int meta[1]);


/* Fold: version 2 (trimmed)
 * Fold long input lines into two or more shorter lines after the last non-blank characters
 * that occurs before the n-th column of input. Make sure your program does something intelligent
 * with very long lines, and if there are no blanks or tabs before the specified column.
 */
int main()
{
	char line_[MAXLENGTH];
    unsigned int len, i;
    int meta[1];

    for (i = 0; i < MAX_LINES; ++i) {
        len = get_line_trimmed(line_, MAXLENGTH, meta);
        printf("%s", line_);

        // overflowed
        if (len == (MAXLENGTH - 1) && !meta[0])
            printf("...");

        printf("\n");

        if (meta[0])
            break;
    }

    return 0;
}


/* Read a trimmed line into string `s`, return length (number of characters).
 * Modifies a array meta with the corresponding data, in sequence:
 * 0: reached EOF (TRUE | FALSE),
 * 1: position of the first entry of the ending blank input sequence.
 *    If the line does not end in blank, meta[1] will be -1.
 */
int get_line_trimmed(char s[], int lim, int meta[1])
{
	char c, lc = EOF;
	int i, trimmed = 0;

	for (i = 0; (i < lim - trimmed - 1)
                && !( meta[0] = (c = getchar()) == '\0' )
                && (c != '\n'); ++i) {

		if (c == '\t')
			c = ' ';
		
		if (c == ' ' && lc == ' ') {
			lc = c;
			++trimmed;
			continue;
		}
		s[i - trimmed] = lc = c;
	}
	if (lc == ' ')
        --i;

	s[i - trimmed] = '\0';

	return i - trimmed;
}
