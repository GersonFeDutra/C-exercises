#include <stdio.h>
#include <stdlib.h>

#define ERR_BEGIN "\033[31m"
#define ERR_END "\033[m"


/* Hexadecimal to Integer
 * Converts a string of hexadecimal digits (including an optional 0x or 0X)
 * into its equivalent integer value.
 */
int htoi(const char s[])
{
    int power(int x, int n);
    int i; // current digit
    int n; // string size
    int x = 0; // target integer
    int o = 0; // 0x offset.

    if (s[i = 0] == '0') {
        if (s[++i] != 'X' && s[i] != 'x')
            return -1;
        o = 2;
    }

    for (n = 0; s[n] != '\0'; n++); // Find the size of the string

    for (i = n - 1; i >= o; i--) {
        int v;
		if (s[i] >= '0' && s[i] <= '9')
            v = s[i] - '0';
        else if (s[i] >= 'A' && s[i] <= 'F')
            v = 10 + s[i] - 'A';
        else if (s[i] >= 'a' && s[i] <= 'f')
            v = 10 + s[i] - 'a';
        else
            return -1;
        x += v * power(16, (n - o - 1) - (i - o));
	}

    return x;
}


/* Write the function htoi(s).
 * The allowable digits are 0 through 9, a through f, and A through F. */
int main(int argc, char const *argv[])
{
    if (argc < 2) {
        fprintf(stderr, ERR_BEGIN
                "Not enough command line arguments. Expects at least one hex number.\n" ERR_END);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        int d = htoi(argv[i]);

        if (d == -1)
            fprintf(stderr, ERR_BEGIN "%d° command line argument is not a hex number.\n" ERR_END, i);
        else
            printf("%d\n", d);
    }

    return EXIT_SUCCESS;
}


/* Returns n power of integer x. */
int power(int x, int n)
{
    int p = 1;

    for (int i = 0; i < n; ++i)
        p *= x;

    return p;
}
