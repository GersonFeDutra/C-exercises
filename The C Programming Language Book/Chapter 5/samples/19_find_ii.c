#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000 /* maximum input line length */

int get_line(char *s, unsigned int lim);
const char *strindex(const char *s, const char t[]);


/* find: print lines that match pattern from 1st arg.
 * options:
 *    -n (number): show line numbers
 *    -x (except): show all lines except those with the given pattern
 */
int main(int argc, char const *argv[])
{
	size_t lineno = 0;
	int c, except, number, found;
	except = number = found = 0;

	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
				case 'x': except = 1; break;
				case 'n': number = 1; break;
				default:
					fprintf(stderr, "\033[31m""Error: Illegal option \033[36m%c\033[m\n", c);
					argc = 0;
					found = -1;
					break;
			}

	if (argc != 1) {
        fprintf(stderr, "\033[33m""Usage: find pattern.\033[m\n");
		fprintf(stderr, "\033[33m""Expects a single string pattern as argument!\033[m\n");
	}
	else {
		char line[MAXLINE];
		int found = 0;
		setbuf(stdout, NULL);

		while (get_line(line, MAXLINE) != EOF) {
			const char *at;
			lineno++;

			if ((at = strstr(line, *argv)) != NULL != except) {
				if (number)
					printf("%Ld: ", lineno);

				if (except)
					printf("%s", line);
				else {
					const char *p;
					for (p = line; p != at; ++p)
						putchar(*p);

					fprintf(stderr, "\033[32m");
					for (const char *c = *argv; *p == *c && *c != '\0'; c++)
						putchar(*p++);
					fprintf(stderr, "\033[m");

					printf("%s", p);
				}
				found++;
			}
		}
	}

	return found;
}


/* Read a line into string `s`. return last read char or EOF: pointer version */
int get_line(char *s, unsigned int lim)
{
	int c;

	for (; lim && ((c = getchar()) != EOF) && (c != '\n'); --lim)
		*s++ = c;

	if (c == '\n')
		*s++ = c;

	*s = '\0';

    return c;
}
