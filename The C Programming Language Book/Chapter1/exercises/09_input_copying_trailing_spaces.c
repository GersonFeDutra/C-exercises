#include <stdio.h>


int main()
{
    int c, lastchar = -1;

    while ((c = getchar()) != EOF) {

        if (c == ' ' && lastchar == ' ')
            continue;
        
        putchar(c);
        lastchar = c;
    }

    return 0;
}

