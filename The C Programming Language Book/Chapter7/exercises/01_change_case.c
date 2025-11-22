#include <stdio.h>
#include <ctype.h>

#define EXIT_SUCCESS 0

/** Write a program that converts upper case to lower or lowercase to upper,
 * depending on the name it is invoked with, as found in argv[0]
 **/
int main(int argc, char *argv[])
{
    int c;

    if (*argv[0] >= 'A' && *argv[0] <= 'Z')
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    else
        while ((c = getchar()) != EOF)
            putchar(toupper(c));

    return EXIT_SUCCESS;
}
