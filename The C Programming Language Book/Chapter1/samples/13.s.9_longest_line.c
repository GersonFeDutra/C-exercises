#include <stdio.h>

#define MAXLINE 100 /* Maximum input line size */

int get_line(char line[], int maxline);
void copy(char to[], char from[]);


/* Print longest input line. */
int main()
{
	int len; // current line length
	int max = 0; // maximum length seen so far
	char line[MAXLINE]; // current input line
	char longest[MAXLINE]; // longest line saved here

	while ((len = get_line(line, MAXLINE)) > 0) {
		
		if (line[0] == '\n' || line[0] == EOF)
			break;
		
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}
	
	// there was a line
	if (max > 0)
		printf("%s", longest);

	return 0;
}

/* Read a line into string `s`, return length. */
int get_line(char s[], int lim)
{
	int c, i;

    // We are using `lim - 1` so the last space will be reserved to '\0'
	for (i = 0; (i < lim - 1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
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
