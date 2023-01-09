#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEF_LN 10   /* default number of lines to read */
#define MAX_LEN 255 /* max length of an input line */

int get_line(char *s, unsigned int lim);


/* Write the program tail, which prints the last n lines of its input.
 * By default, n is 10, let us say, but it can be changed by an optional argument,
 * so that `tail -n` prints the last n lines.
// TODO
 * The program should behave rationally no matter how unreasonable the input or the value of n.
 * Write the program so it makes best use of available storage; lines should be stored as in the
 * sorting program of Section 5.6, not in a two-dimensional array of fixed size. */
int main(int argc, char const *argv[])
{
    unsigned lines = DEF_LN;

    if (argc > 1) {
        if (argv[1][0] != '-')
            fprintf(stderr, "\033[33m""Invalid command line argument.\n"
                    "Expects -n where n is the number of lines to output.\n"
                    "Fallback to default: %d.\033[m\n", lines);
        else
            lines = abs(atoi(argv[1] + 1));
    }

    /* we add 1, since the last line may be a final blank */
    char text[lines += 1][MAX_LEN];
    int line, read;

    for (read = line = 0; get_line(text[line], MAX_LEN) != EOF; line = (line + 1) % lines)
        if (read < lines)
            read++;

    for (line = (lines + line - (read - 1)) % lines; read > 0; --read, line = ++line % lines)
        printf("%s\n", text[line]);

    return EXIT_SUCCESS;
}


/* Read a line into string `s`. return last read char or EOF: pointer version
 * ignores '\n' character */
int get_line(char *s, unsigned int lim)
{
	int c;

	for (; lim && ((c = getchar()) != EOF) && (c != '\n'); --lim)
		*s++ = c;

	// if (c == '\n')
	// 	*s++ = c;

	*s = '\0';

    return c;
}
