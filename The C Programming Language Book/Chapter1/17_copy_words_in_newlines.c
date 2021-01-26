#include <stdio.h>


/* prints each word in newlines */
int main()
{
    int c, last_char = -1;

    while ((c = getchar()) != EOF) {

        if (c == ' ' || c == '\t') {

            if (last_char != ' ' && last_char != '\t')
                putchar('\n');
        }
        else{
            putchar(c);
        }
        last_char = c;
    }
    
    return 0;
}
