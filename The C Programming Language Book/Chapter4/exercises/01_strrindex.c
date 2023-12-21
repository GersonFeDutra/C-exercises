#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000 /* maximum input line length */
int getline_(char s[], int lim);


/* strindex: returns the position of the rightmost
 * occurrence of t in s, or -1 if there is none. */
int strrindex(const char s[], const char t[])
{
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;

		if (k > 0 && t[k] == '\0')
			return j;
	}

	return -1;
}


/* Write a function strrindex(s,t) */
int main(int argc, char const *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "\033[31mError! No string pattern passed as argument!\033[m\n");

		return -1;
	}

	char line[MAXLINE];
	int found = 0;
	int index;
	int len = strlen(argv[1]);
	setbuf(stdout, NULL);

	while (getline_(line, MAXLINE) > 0)
		if ((index = strrindex(line, argv[1])) >= 0) {
			int i;

			for (i = 0; i < index - len; ++i)
				putchar(line[i]);

			fprintf(stderr, "\033[32m");

			while (i < index)
				putchar(line[i++]);

			fprintf(stderr, "\033[m");
			printf("%s", line + i);
			found++;
		}

	return found;
}


/* getline_: get line into s, return length */
int getline_(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}
