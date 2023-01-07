#include <stdio.h>
#include <stdlib.h>


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


#define BUF_LEN 255
int main(int argc, char *argv[])
{
    int len = BUF_LEN;
    if (argc < 2)
        fprintf(stderr, "\033[33m""Using default line buffer length of 255. "
                "Use a numeric argument to change it\033[31m\n");
    else
        len = atoi(argv[1]);

    char str[len];

    get_line(str, len);
    fprintf(stderr, "\033[32m");
    printf(str);
    fprintf(stderr, "\033[m\n");

    return EXIT_SUCCESS;
}
