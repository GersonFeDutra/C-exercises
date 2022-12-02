#include <stdio.h>

#define FALSE 0
#define TRUE  1

#define NONE             0
#define ON_QUOTES        1
#define ON_SINGLE_QUOTES 2


/* Check ballance
 * Checks a C  program for rudimentary syntax errors like unbalanced parentheses, brackets, braces,
 * qutos, escape sequences and comments.
 */
int main() {
    char _for[] = "for";
    int c;
    int _last3[3] = { '\0', '\0', '\0' };
    unsigned short int state = NONE, has_lonely_pair, is_esc_seq, on_for;
    unsigned int parenths, brackts, braces, for_colons;
    unsigned long int row, col, quote_row, quote_col;
    has_lonely_pair = is_esc_seq = on_for = FALSE;
    quote_row = quote_col = row = col = parenths = brackts = braces = for_colons = 0;

    while ((c = getchar()) != EOF) {

        if (!on_for) {
            on_for = TRUE;
            for (int i = 0; i < 3; ++i)
                if (_last3[i] != _for[i]) {
                    on_for = FALSE;
                    break;
                }
        }

        if (is_esc_seq) {
            is_esc_seq = FALSE;
            if (state == NONE) {
                if (c != '\n')
                    printf("Error! Invalid character \\ at (row:%lu, col:%lu).\n", row, col);
            }
            else switch (c) {
                case '\\':
                case '\'':
                case '"':
                case 'n':
                case 't':
                    break;
                default: printf("Error! Invalid escape sequence \\%c at (row:%lu, col:%lu).\n",
                                 c, row, col);
            }
        }
        else {
            switch (c) {
                case '(': {
                    ++parenths;
                    has_lonely_pair = FALSE;
                } break;
                case ')': has_lonely_pair = --parenths < 0; break;
                case '[': {
                    ++brackts;
                    has_lonely_pair = FALSE;
                } break;
                case ']': has_lonely_pair = --brackts < 0; break;
                case '{': {
                    ++braces;
                    has_lonely_pair = FALSE;
                } break;
                case '}': has_lonely_pair = --braces < 0; break;
            }
            if (has_lonely_pair)
                printf("Error! Lonely closing pair `%c` at (row:%lu, col:%lu).\n", c, row, col);

            switch (c) {
                case '\\': is_esc_seq = TRUE; break;
                case ';': {
                    if (on_for) {
                        if (++for_colons == 2)
                            on_for = FALSE;
                        break;
                    }
                    if (parenths > 0)
                        printf("Error! Unclosed parentheses at line#%lu.\n", row + 1);
                    if (brackts > 0)
                        printf("Error! Unclosed brackets at line#%lu.\n", row + 1);
                    parenths = brackts = 0;
                } break;
                case '\n': {
                    ++row;
                    col = 0;
                } break;
                case '\'': {
                    switch (state) {
                        case ON_SINGLE_QUOTES: state = NONE; break;
                        case NONE: state = ON_SINGLE_QUOTES; break;
                    }
                } break;
                case '"': {
                    switch (state) {
                        case ON_QUOTES: state = NONE; break;
                        case NONE: {
                            quote_row = row;
                            quote_col = col;
                            state = ON_QUOTES;
                        } break;
                    }
                }
            }
        }

        ++col;
        _last3[0] = _last3[1];
        _last3[1] = _last3[2];
        _last3[2] = c;
        //putchar(c);
    }

    if (parenths)
        printf("Error! Unclosed parentheses.\n");
    if (brackts)
        printf("Error! Unclosed brackets.\n");
    if (braces)
        printf("Error! Unclosed braces.\n");
    // FIXME -> Counting error
    if (ON_QUOTES)
        printf("Error! Unclosed quotes at: (row:%lu, col:%lu).\n", quote_row, quote_col);
}
