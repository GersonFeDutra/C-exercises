#include <stdio.h>

#define MAX_LINE 100 /* Maximum input line size */
#define FALSE 0
#define TRUE 1


/* Print longest input line. */
int main()
{
	char line[MAX_LINE];

	get_line_trimmed(line, MAX_LINE);
	printf("\nTrimmed: %s", line);

	return 0;
}


/* Read a trimmed line into string `s`, return length (number of characters). */
int get_line_trimmed(char s[], int lim)
{
	char c, lc = EOF;
	int i, trimmed = 0;

	for (i = 0; (i < lim - trimmed - 1) && ((c = getchar()) != '\0') && (c != '\n'); ++i) {

		if (c == '\t')
			c = ' ';
		
		if (c == ' ' && lc == ' ') {
			lc = c;
			++trimmed;
			continue;
		}
		s[i - trimmed] = lc = c;
	}
	
	s[i - trimmed] = '\0';

	return i - trimmed;
}
