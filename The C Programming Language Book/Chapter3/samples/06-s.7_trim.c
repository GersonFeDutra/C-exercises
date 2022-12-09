#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* trim: remove trailing blanks, tabs, newlines */
int trim(char s[])
{
    int n;

    for (n = strlen(s) - 1; n >= 0; n--)
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
            break;

    s[++n] = '\0';

    return n;
}


int main(int argc, char const *argv[])
{
    if (argc < 2)
        fprintf(stderr, "\033[33mWarning! Expected at least one argument to be trimmed.\033[m\n");

    setbuf(stdout, NULL);

    for (int i = 1; i < argc; ++i) {
        char s[strlen(argv[i])];
        strcpy(s, argv[i]);

        int len = trim(s);
        printf("%s", s);
		fprintf(stderr, "\033[34m [length: %d]\033[m", len);
        putchar('\n');
	}

    return EXIT_SUCCESS;
}
