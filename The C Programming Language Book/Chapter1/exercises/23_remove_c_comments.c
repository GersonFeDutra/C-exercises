#include <stdio.h>

#define FALSE 0
#define TRUE 1

#define NORMAL 0
#define INLINE_COMMENT 1
#define MULTILINE_COMMENT 2
#define IN_QUOTES 3
#define IN_SINGLE_QUOTES 4


/* Remove all comments:
 * Remove comments from a C program, treating quoted strings and character constants properly.
 */
int main()
{
	int c, lc = getchar();
	unsigned int state = NORMAL, can_print;

	setbuf(stdout, NULL); // Flush stdout directly to output as stderr is as well

	if (lc == EOF)
		return 0;
	switch (lc) {
		case EOF: return 0;
		case '\'': state = IN_SINGLE_QUOTES; break;
		case '"': state = IN_QUOTES; break;
	}

	while ((c = getchar()) != EOF) {
		can_print = TRUE;

		if (lc == '\\') {
			switch (state) {
				case INLINE_COMMENT:
				case MULTILINE_COMMENT:
					break;
				default: {
					putchar(lc);
					lc = c;
				}
			}
			continue;
		}

		switch (state) {
			case IN_SINGLE_QUOTES: {
				if (lc == '\\') {
					state = NORMAL;
					putchar(lc);
					lc = '\0';
					continue;
				}
				else {
					state = NORMAL;
				}
			}
			case NORMAL: {
				can_print = TRUE;
				switch (lc) {
					case '/': {
						if (c == '*')
							state = MULTILINE_COMMENT;
						else if (c == '/')
							state = INLINE_COMMENT;
						can_print = FALSE;
					} break;
					case '\'': state = IN_SINGLE_QUOTES; break;
					case '"': state = IN_QUOTES; break;
				}
			} break;
			case IN_QUOTES: {
				if (lc == '"')
					state = NORMAL;
			} break;
			case INLINE_COMMENT: {
				if (c == '\n' || (lc == '/' && c == '/'))
					state = NORMAL;
				can_print = FALSE;
			} break;
			case MULTILINE_COMMENT: {
				if (lc == '*' && c == '/')
					state = NORMAL;
				can_print = FALSE;
			}
		}

		if (can_print)
			putchar(lc);
		else
			fprintf(stderr, "\e[01;31m" "%c" "\e[0m", lc);
		lc = c;
	}
	putchar(lc);
}
