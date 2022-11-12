#include <stdio.h>

#define FALSE 0
#define TRUE 1

#define NONE 0
#define ON_QUOTES 1
#define ON_SINGLE_QUOTES 2
#define ERR_BEGIN "\e[01;31m" // Color stderr output to red.
#define ERR_END "\e[0m" // Return stderr to normal style.

struct check {
	int what;          // What character was returned
	unsigned long row; // in which row
	unsigned long col; // in which column
}; // helper struct to the `pairs_check` function

struct check pairs_check(unsigned long int row, unsigned long int col);

/* Check balance
 * Checks a C  program for rudimentary syntax errors like unbalanced parentheses, brackets, braces,
 * quotes, escape sequences and comments.
 */
int main()
{
	struct check c = {.row = 1, .col = 0, .what = '\0'};

	do {
		switch ((c = pairs_check(c.row, c.col)).what) {
			case ')':
			case ']':
			case '}':
				fprintf(stderr, "Lonely `%c` at (row:%lu col:%lu).\n", c.what, c.row, c.col);
		}
	} while (c.what != EOF);
}


/* Checks for the next escape sequence, returns \0 when \\ is being found. */
char check_esc_seq(struct check check)
{
	switch (check.what) {
		case 'a':
		case 'b':
		case 'e':
		case 'f':
		case 'n':
		case 'r':
		case 't':
		case 'v':
		case '\'':
		case '"':
		case '?':
		case 'x':
		case 'u':
		case 'U':
		case '\n':
			break;
		case '\\':
			return '\0';
			// Usado para desconsiderar o escape no próximo passo em `pairs_check`
		default:
			if (check.what < '0' || check.what > '9')
				fprintf(stderr, ERR_BEGIN "Error! Invalid escape sequence \\%c at "
						"(row:%lu, col:%lu).\n" ERR_END, check.what, check.row, check.col);
	}
	return check.what;
}


/* Gets next character to be checked, increasing mapping accordingly. */
struct check next(struct check prev)
{
	if ((prev.what = getchar()) == '\n') {
		prev.row++;
		prev.col = 0;
	}
	else {
		prev.col++;
	}
	if (prev.what > 0) // NOT EOF or control characters
		putchar(prev.what);
	return prev;
}

/* Pop a value and append a new one in the array "queue-like". */
unsigned int poppend(char x, char arr[], unsigned int size, unsigned int at)
{
	arr[at] = x;
	return ++at % size;
}


/* Assuming the double quotes context, find the closing quotes. */
struct check quotes_check(struct check c)
{
	while ((c = next(c)).what != '"') {
		switch (c.what) {
			case EOF:
			case '\n':
				fprintf(stderr, ERR_BEGIN "Error! Unclosed quotes at (row:%lu, col:%lu).\n"
						ERR_END, c.row, c.col);
				return c;
		}
		if (c.what == '\\')
			c.what = check_esc_seq(c = next(c)); // Double quotes escape sequence
	}

	return c;
}


/* Assuming the single quotes context, find the closing quote. */
struct check quote_check(struct check c)
{
	unsigned long row = c.row;
	unsigned long col = c.col;
	char lc = c.what; // last character

	if ((c = next(c)).what != '\'') {
		switch (c.what) {
			case EOF:
			case '\n':
				break;
			case '\\': c.what = check_esc_seq(c = next(c)); // Single quotes escape sequence
			default: c = next(c);
		}
		if (c.what != '\'')
			fprintf(stderr, ERR_BEGIN "Error! Unclosed character constant `'` at "
					"(row:%lu, col:%lu).\n" ERR_END, row, col);
	}
	return c;
}


struct check pair_check(struct check check, char closing_pair, char pair_name[])
{
	struct check c = check;
	if ((c = pairs_check(c.row, c.col)).what != closing_pair) {
		if (c.what == ';' || c.what == EOF)
			fprintf(stderr, ERR_BEGIN "Error! Unclosed %s `%c` at (row:%lu, col:%lu).\n" ERR_END,
					pair_name, closing_pair, check.row, check.col);
		else
			fprintf(stderr, ERR_BEGIN "Error! Unexpected closing pair `%c` at "
					"(row:%lu, col:%lu).\n" ERR_END, c.what, c.row, c.col);
	}
	return c;
}


#define LC_SIZE 3 // Quantity of last captured characters in cache.
/* Pairs Check
 * Checks for balance, comments and scape sequences.
 * Returns a lonely closing pair, \0, `;` or EOF.
 */
struct check pairs_check(unsigned long int row, unsigned long int col)
{
	unsigned int ln = 0;            // last captured character position.
	char lc[] = {'\0', '\0', '\0'}; // cache the last captured characters.
	struct check check = {.row = row, .col = col, .what = '\0'};

	while ((check = next(check)).what != EOF) {

		// on for
		if (lc[ln] == 'f' && lc[(ln + 1) % LC_SIZE] == 'o' && lc[(ln + 2) % LC_SIZE] == 'r') {
			unsigned short int colons = 0;

			while ((check = next(check)).what != '(') {
				switch (check.what) {
					case EOF: fprintf(stderr, ERR_BEGIN "Error! Expected for `(;;)` statement body."
							ERR_END); return check;
					case ' ':
					case '\t':
					case '\n':
						break; // Blank character
					case '\\': {
						if ((check = next(check)).what == '\n')
							break; // Forced break
					} // We do not check for comments between the for statement and body
					default:
						fprintf(stderr, ERR_BEGIN "Error! Expected for `(;;)` statements body."
								ERR_END);
					}
			}

			do {
				// TODO -> Ignorar se está entre aspas ou aspas simples.
				if (check.what == ';') {
					if (++colons > 2) {
						fprintf(stderr, ERR_BEGIN "Error! Unexpected colon at (row:%lu, col:%lu). "
								ERR_END "Unclosed for statement.", check.row, check.col);
						break;
					}
				}
				else if (check.what == EOF) {
					fprintf(stderr, ERR_BEGIN "Error! For statements must be between parentheses "
							ERR_END "at (row:%lu, col:%lu).", check.row, check.col);
					return check;
				}
			} while ((check = next(check)).what != ')');

			if (colons < 2)
				fprintf(stderr, ERR_BEGIN "Error! Incomplete for expressions body." ERR_END);

			// Clear the lc cache
			for (int i = 0; i < LC_SIZE; ++i)
				lc[i] = '\0';
			continue;
		}

		switch (check.what) {
			case ';':
			case ')':
			case ']':
			case '}':
                return check;
			case '(': check = pair_check(check, ')', "parentheses"); break;
			case '[': check = pair_check(check, ']', "brackets"); break;
			case '{': {
				struct check c = check;
				while ((c = pairs_check(c.row, c.col)).what != '}') {
					if (c.what == ';')
						continue;

					if (c.what == EOF) {
						fprintf(stderr, ERR_BEGIN "Error! Unclosed braces `}` at "
								"(row:%lu, col:%lu).\n" ERR_END, check.row, check.col);
						break;
					}
					fprintf(stderr, ERR_BEGIN "Error! Unexpected closing pair `%c` at "
							"(row:%lu, col:%lu).\n" ERR_END, c.what, c.row, c.col);
				}
				check = c;
			}; break;
			case '/': {
				if (lc[ln] == '/') {
					while ((check = next(check)).what != '\n')
						if (check.what == EOF)
							return check;
					ln = poppend(check.what, lc, LC_SIZE, ln);
				}
				else if (lc[ln] == '*') {
					while ((check = next(check)).what != '/' && lc[ln] != '*') {
						if (check.what == EOF)
							return check;
						ln = poppend(check.what, lc, LC_SIZE, ln);
					}
				}
			} break;
			case '\'': {
				check = quote_check(check);
				ln = poppend('\0', lc, LC_SIZE, ln);
			} break;
			case '"': {
				check = quotes_check(check);
				ln = poppend('\0', lc, LC_SIZE, ln);
			}; break;
			default: {
				if (lc[(ln + LC_SIZE - 1) % LC_SIZE] == '\\') {
					if (check.what == '\n') { // usado para quebrar expressões em múltiplas linhas
						ln = poppend(check.what, lc, LC_SIZE, ln);
						continue;
					}
					fprintf(stderr, ERR_BEGIN "Error! Invalid character \\ at (row:%lu, col:%lu).\n"
							ERR_END, check.row, check.col);
				}
				ln = poppend(check.what, lc, LC_SIZE, ln);
			} break;
		}
	}
	return check;
}
