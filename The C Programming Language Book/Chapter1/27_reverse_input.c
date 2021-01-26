#include <stdio.h>

#define MAX_LINE 100


int main()
{
	char line[MAX_LINE], reversed[MAX_LINE];
	int size = get_line_trimmed(line, MAX_LINE);

	reverse_line(line, reversed, size);
	printf("\nTrimmed and Reversed: %s", reversed);

	return 0;
}

/* Reverse the string to another; size is the number of characters. */
void reverse_line(char from[], char to[], int size)
{
	int i;
	
	for (i = size - 1; i >= 0; --i) {
		to[size - i - 1] = from[i];
	}
	to[size] = '\0';
}


/* Read a trimmed line into string `s`, return length. */
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

	return (i - trimmed);
}
