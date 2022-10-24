#include <stdio.h>

#define MAX_LINE 80 /* Maximum input line size */
#define FALSE 0
#define TRUE 1

int get_line(char line[], int maxline);
void copy(char to[], char from[]);


/* Print longest input line. */
int main()
{
	const int MAXCHAR = MAX_LINE - 1; // maximum character index
	int len; // current line length
	int isoverflow = FALSE; // line is bigger than MAX_LINE

	char line[MAX_LINE]; // current input line
	char overcached[MAX_LINE]; // cache a overflow line

	while ((len = get_line(line, MAX_LINE)) > 0) {
		
		if (line[0] == '\n' || line[0] == EOF)
			break;
		
		int overflowed = (len == MAXCHAR); // line is bigger than limit
		int wasoverflow = isoverflow;
		
		if (!wasoverflow && overflowed)
				copy(overcached, line);
		
		isoverflow = (
				overflowed && line[MAXCHAR] != '\n' && line[MAXCHAR] != EOF
		);
		
		if (wasoverflow && !isoverflow)
			printf("\nText: %s...\n", overcached);
	}

	return 0;
}


/* Read a line into string `s`, return length (number of characters). */
int get_line(char s[], int lim)
{
	char c;
	int i;

	for (i = 0; (i < lim - 1) && ((c = getchar()) != '\0') && (c != '\n'); ++i)
		s[i] = c;
	
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	
	s[i] = '\0';

	return i;
}


/* Copy `from` into `to`; assume to is big enough. */
void copy(char to[], char from[])
{
	int i = 0;
	
	while ((to[i] = from[i]) != '\0')
		++i;
}
