#include <stdio.h>
#include <stdlib.h>


/* atoi: convert s to integer: pointer version */
int atoi(const char *s)
{
    return (int) atof(s);
}


/* Sum integers passed as arguments to the program. */
int main(int argc, char const *argv[])
{
	if (argc < 3) {
		fprintf(stderr,
			"\033[31mNot enough command line argument. Expects at least one number.\033[m\n");
		return EXIT_FAILURE;
	}

	int t = atoi(argv[1]);
	fprintf(stderr, "\033[34m%d", t);

	for (int i = 2; i < argc; ++i) {
		int x = atoi(argv[i]);
		t += x;
		fprintf(stderr, " + %d", x);
	}

	fprintf(stderr, " = \033[m");
	printf("%d\n", t);

	return EXIT_SUCCESS;
}
