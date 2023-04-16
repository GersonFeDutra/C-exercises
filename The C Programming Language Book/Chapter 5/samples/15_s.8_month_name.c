#include <stdio.h>
#include <stdlib.h>


/* month_name: return name of n-th month */
char *month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December",
    };

    return (n < 1 || n > 12) ? name[0] : name[n];
}


int main(int argc, char const *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "\033[31m""Error: Expected an integer as argument.\033[m\n");
        return EXIT_FAILURE;
    }

    char *m = month_name(atoi(argv[1]));
    if (*m == 'I') {
        fprintf(stderr, "\033[31m""Error: Invalid month.\033[m\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", m);

    return EXIT_SUCCESS;
}
