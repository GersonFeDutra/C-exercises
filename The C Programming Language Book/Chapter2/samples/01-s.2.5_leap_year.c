#include <stdio.h>
#include <stdlib.h>


/* Checks for a leap year. Expects an integer as the CLI argument. */
int main(int argc, char const *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "No command line argument. Expects an integer.");
        return EXIT_FAILURE;
    }

    int year = atoi(argv[1]);

    printf("%d %s a leap year.\n", year,
        ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? "is" : "is not"
    );

    return EXIT_SUCCESS;
}
