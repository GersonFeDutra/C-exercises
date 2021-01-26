#include <stdio.h>

#define MAXLINE 100 /* Maximum input line size */

int get_line(void);
void copy(void);

int max; // maximum length seen so far
char line[MAXLINE]; // current input line
char longest[MAXLINE]; // longest line saved here


/* Print longest input line; specialized version. */
int main()
{
	extern int max;
	extern char longest[];
	
	int len; // current line length
	max = 0;

	while ((len = get_line()) > 0) {
		
		if (line[0] == '\n' || line[0] == EOF)
			break;
		
		if (len > max) {
			max = len;
			copy();
		}
	}
	
	// there was a line
	if (max > 0)
		printf("%s", longest);

	return 0;
}

/* getline: specialized version. */
int get_line(void)
{
	extern char line[];
	char c;
	int i;

	for (i = 0; (i < MAXLINE - 1) && ( (c = getchar()) != EOF ) && (c != '\n'); ++i)
		line[i] = c;
	
	if (c == '\n') {
		line[i] = c;
		++i;
	}

	line[i] = '\0';

	return i;
}


/* Copy: specialized version. */
void copy(void)
{
	extern char line[], longest[];
	int i = 0;
	
	while ( (longest[i] = line[i]) != '\0' )
		++i;
}
