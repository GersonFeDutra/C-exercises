#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/** Write a program that will print arbitrary input in a sensible way.
 * As a minimum, it should print non-graphic characters in octal or hexadecimal
 * according to local custom, and break long text lines.
 * 
 * @note Usage: [-o] octal (default hex)
 **/
int main(int argc, char *argv[])
{
    #define bool unsigned char
    #define true 1
    #define false 0

    void echo(const char *format);

    bool use_octal = false;
    use_octal = argc > 1 && **(++argv) == '-' && *(*argv + 1) == 'o';

    if (use_octal)
        echo("\\0o%03o");
    else
        echo("\\0x%03x");

    return EXIT_SUCCESS;
}

void echo(const char *format)
{
    int c;
    int break_symbol = 0;

    while ((c = getchar()) != EOF) {
        if (isprint(c)) {
            if (break_symbol == '.' && isspace(c)) {
                break_symbol = '\0';
                putchar('\n');
            }
            else
                putchar(c);
        }
        else if (c == '\n') {
            putchar('\n');
            break_symbol = '\0';
        }
        else if (c != '\r') {
            if (break_symbol == '\r')
                if (c == '\f') {
                    putchar('\n');
                    continue;
                }
                else
                    putchar(break_symbol);

            printf(format, c);
        }
        break_symbol = c;
    }
    putchar('\n');
}
