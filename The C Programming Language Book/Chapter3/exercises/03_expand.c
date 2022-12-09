#include <stdio.h>
#include <stdlib.h>


/* Expand:
 * Expands shorthand notations like a-z in the string s1 into the equivalent
 * complete list abc..xyz in s2 (assumes s2 is big enough).
 */
void expand(const char s1[], char s2[])
{
    char sep = '\0', start, end;
    int i = 0, j = 0;

    if (s1[0] == '\0') {
        s2[0] = '\0';
        return;
    }

    if (s1[0] == '-')
        sep = '-', i++; // Uses separator

	if (s1[i + 1] == '-') { // captures a sequence
		if (s1[i + 2] == '\0') {
			// Malformed sequence: just adds the first character.
			s2[0] = s1[i];
            s2[1] = '\0';
            return;
        }

        if (s1[i + 2] < s1[i]) {
            // Expands in descending order
            if (sep == '\0') {
                for (start = s1[i], end = s1[i + 2]; start >= end; --start)
                    s2[j++] = start;
            } else {
                for (start = s1[i], end = s1[i + 2]; start > end; --start)
                    s2[j] = start, ++j, s2[j++] = sep;
                s2[j++] = start; // The "final" char that is equal to `end` added without separator.
            }
        }
        else {
            // Expands in ascending order
            if (sep == '\0') {
                for (start = s1[i], end = s1[i + 2]; start <= end; ++start)
                    s2[j++] = start;
            } else {
                for (start = s1[i], end = s1[i + 2]; start < end; ++start)
                    s2[j] = start, ++j, s2[j++] = sep;
                s2[j++] = start; // The "final" char that is equal to `end` added without separator.
            }
        }

        i += 3;
	}
	else { // Uses no sequence
		s2[j++] = s1[i++];
	}

    if (s1[i] == ' ')
        s2[j++] = ' ', i++; // Adds a space, but won't use it as separator
    else if (s1[i] == '-')
        s2[j++] = '-'; // Adds a hyphen, and will use it as separator.

	// Expands further shortcuts.
    expand(s1 + i, s2 + j);
}


/* Write a function expand(s1, s2).
 * Allows for letters in either case and digits, and be prepared to handle cases like a-b-c.
 * and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.
 */
int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr,
                "\033[31mError! No shortcut expression informed, expected eg.: -a-z 0-9, "
                "expands to: a-b-c...-x-y-z 0123456789\033[m\n");
        return EXIT_FAILURE;
    }
    int get_expansion_length(const char s[]);

    char ex[get_expansion_length(argv[1])];

    expand(argv[1], ex);
    printf("%s\n", ex);

    return EXIT_SUCCESS;
}


/* Given the `expand(s1, s2)` method, calculates the size necessary to expand s1 (s) into s2. */
int get_expansion_length(const char s[])
{
    int len = 0;
	int i = 0, uses_sep = 0;

	if (s[0] == '\0')
		return 1;

	if (s[0] == '-')
		uses_sep = 1, i++; // Uses separator

	if (s[i + 1] == '-') { // captures a sequence
		if (s[i + 2] == '\0')
			// Malformed sequence: just adds the first character and finish string ('\0').
			return 2;

		if (s[i + 2] < s[i]) {
			// Counts the expansion in descending order
            len = uses_sep
                ? 2 * (s[i] - s[i + 2]) + 1 // 2*(start - end) + 1
                : s[i] - s[i + 2] + 1; // start - end + 1
		}
		else {
			// Counts the expansion in ascending order
            len = uses_sep
                ? 2 * (s[i + 2] - s[i]) + 1 // 2*(end - start) + 1
                : s[i + 2] - s[i] + 1; // end - start + 1
		}

	    i += 3;
	} else { // Uses no sequence
		len = 1;
        i++;
    }

	if (s[i] == ' ')
		len++, i++; // Adds a space, but won't use it as separator
	else if (s[i] == '-')
		len++; // Adds a hyphen, and will use it as separator.

	return len + get_expansion_length(s + i);
}
