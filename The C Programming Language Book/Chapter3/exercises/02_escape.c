#include <stdio.h>
#include <stdlib.h>


/* escape: converts characters like newline and tab into visible escape sequences
 * like \n and \t as it copies the string s to t.
 * Assumes t is big enough (2 * length of s). */
void escape(const char s[], char t[])
{
    int i, j;

    for (j = i = 0; s[i] != '\0'; ++i, ++j)
        switch (s[i]) {
            case '\t': {
                t[j++] = '\\';
                t[j] = 't';
            } break;
            case '\n': {
                t[j++] = '\\';
                t[j] = 'n';
            } break;
            case '\\': {
                t[j++] = '\\';
                t[j] = '\\';
            } break;
            case '\'': {
                t[j++] = '\'';
                t[j] = '\'';
            } break;
            case '\"': {
                t[j++] = '\"';
                t[j] = '\"';
            } break;
            default:
                t[j] = s[i];
                break;
        }

    t[j] = '\0';
}


/* escape: converts escape sequences to its equivalent characters as it copies the string s to t.
 * Assumes s is big enough (half the size of s, at least). */
void descape(const char s[], char t[])
{
    int i, j;

    for (j = i = 0; s[i] != '\0'; ++i, ++j)
        if (s[i] == '\\')
            switch (s[++i]) {
                case 't': t[j] = '\t'; break;
                case 'n': t[j] = '\n'; break;
                case '\\': t[j] = '\\'; break;
                case '\'': t[j] = '\''; break;
                case '\"': t[j] = '\"'; break;
                default: t[j] = s[i]; break;
            }
        else
            t[j] = s[i];

    t[j] = '\0';
}


#define BUF_LEN 255
/* Writes a function escape using a switch. Write a function for the other direction as well. */
int main(void)
{
    int c, i = 0;
    char buf[BUF_LEN];
    char escaped[BUF_LEN * 2];
    setbuf(stdout, NULL);

	while ((c = getchar()) != EOF) {
        buf[i++] = c;
        if (i + 2 == BUF_LEN) {
            buf[i] = '\0';

            escape(buf, escaped);
            printf("%s", escaped);

            descape(escaped, buf);
            fprintf(stderr, "\033[34m%s\033[m", buf);
            i = 0;
        }
    }

    if (i + 2 != BUF_LEN) {
        buf[i] = '\0';
        escape(buf, escaped);
        printf("%s", escaped);

		descape(escaped, buf);
		fprintf(stderr, "\033[34m%s\033[m", buf);
	}

	putchar('\n');

    return EXIT_SUCCESS;
}
