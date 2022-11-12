#include <stdio.h>

#define MAXLENGTH 100

int get_text(char text[], int limit, int meta[2]);


// TODO -> version 2: makes individual lines to be shortened. limit to a x number of lines
/* Fold:
 * Fold long input lines into two or more shorter lines after the last non-blank characters
 * that occurs before the n-th column of input. Make sure your program does something intelligent
 * with very long lines, and if there are no blanks or tabs before the specified column.
 */
int main()
{
	//const int length = MAXLENGTH - 1;
	char line_[MAXLENGTH];
    unsigned int len;
	int c;
    int meta[2];

    len = get_text(line_, MAXLENGTH, meta);

    // overflowed
    //printf("[%d %d, %d: %c]", meta[0], meta[1], len, len == MAXLENGTH - 1 ? 't' : 'f');
    if (len == (MAXLENGTH - 1)) {

        if (meta[1] == -1) {
            printf("%s", line_);
            while ((c = getchar()) != ' ' && c != '\t' && c != '\n' && c == EOF)
                putchar('c');
        } else {
            // "Trimma" o final da linha.
            line_[meta[1]] = '\0';
            printf("%s", line_);
        }
        printf("...\n");
    } else {
        printf("%s\n", line_);
    }

	return 0;
}


/* Get Text
 * Read a text stream into string `s` until limit or EOF, return length (number of characters).
 * Modifies a array meta with the corresponding data, in sequence:
 * 0: reached EOF (TRUE | FALSE),
 * 1: position of the first entry of the ending blank input sequence.
 *    If the line does not end in blank, meta[1] will be -1.
 */
int get_text(char s[], int lim, int meta[2])
{
	int c, i;
    meta[1] = -1; // not on sequence

	for (i = 0; (i < lim - 1) && !(meta[0] = (c = getchar()) == EOF); ++i) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (meta[1] == -1)
                meta[1] = i;
        } else {
            meta[1] = -1;
        }
		s[i] = c;
    }
	
	s[i] = '\0';

	return i;
}
