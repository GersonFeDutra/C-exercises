#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLINE 1000 /* maximum input line length */

int get_line(char *s, unsigned int lim, FILE *ifp);
const char *strindex(const char *s, const char t[], FILE *ifp);


/** find:
 * Modify the pattern finding program of Chapter 5 to take its input from a set
 * of named files or, if no files are named as arguments, from the standard
 * input. Should the file name be printed when a matching line is found?
 *
 * @brief print lines that match pattern from 1st arg.
 *
 * @note Usage: ./find pattern file1 [file2 ...] [-n|--number] [-x|--except]
 * options:
 *    -n | --number: show line numbers
 *    -x | --except: show all lines except those with the given pattern
 **/
int main(int argc, char const *argv[])
{
	const char **current_file = NULL, *pattern = NULL;
	size_t lineno = 0, files_count = 0;
	bool except = false, number = false, single_file;
	long found = 0;
	int c;

	if (argc < 3) {
		switch (argc)
		{
		case 1:
			fprintf(stderr, "\033[33m""Expects a single string pattern as argument!\033[m\n");
			break;
		case 2:
			fprintf(stderr, "\033[33m""Expects at least one file as argument!\033[m\n");
			break;
		}
        fprintf(stderr, "\033[31m""Usage (find pattern): ./find pattern file1 [file2 ...] [-n|--number] [-x|--except]\033[m\n");
	}

	while (--argc > 0)
		if ((*++argv)[0] == '-')
			switch (c = *++argv[0]) {
				case 'x': except = 1; break;
				case 'n': number = 1; break;
				default: {
					if (c != '\0' && (c = *++argv[0]) == '-') {
						if (strcmp(argv[0], "except") == 0)
							except = true;
						else if (strcmp(argv[0], "number") == 0)
							number = true;
					}
					fprintf(stderr, "\033[31m""Error: Illegal option \033[36m%c\033[m\n", c);
					return found = -1;
				} break;
			}
		else if (pattern == NULL)
			pattern = *argv;
		else {
			++files_count;
			if (current_file == NULL)
				current_file = argv;
		}

	single_file = files_count == 1;
	char line[MAXLINE];
	setbuf(stdout, NULL);

	for (; files_count-- != 0; ++current_file) {
		while (**current_file == '-'); // skip options

		FILE *ifp = fopen(*current_file, "r");
		if (ifp == NULL) {
			fprintf(stderr, "\033[31m""Can't open file '%s'\033[m\n", *current_file);
			continue;
		}

		while (get_line(line, MAXLINE, ifp) != EOF) {
			const char *at;
			lineno++;

			if ((at = strstr(line, pattern)) != NULL != except) {
				if (!single_file)
					printf("%s:\n\t", *current_file);

				if (number)
					printf("%Ld: ", lineno);

				if (except)
					printf("%s", line);
				else {
					const char *p;
					for (p = line; p != at; ++p)
						putchar(*p);

					fprintf(stderr, "\033[32m");
					for (const char *c = pattern; *p == *c && *c != '\0'; c++)
						putchar(*p++);
					fprintf(stderr, "\033[m");

					printf("%s", p);
				}
				found++;
				putchar('\n');
			}
		}
	}

	return found;
}


/* Read a line into string `s`. return last read char or EOF: pointer version */
int get_line(char *s, unsigned int lim, FILE *ifp)
{
	int c;

	for (; lim && ((c = getc(ifp)) != EOF) && (c != '\n'); --lim)
		*s++ = c;

	if (c == '\n')
		*s++ = c;

	*s = '\0';

    return c;
}
