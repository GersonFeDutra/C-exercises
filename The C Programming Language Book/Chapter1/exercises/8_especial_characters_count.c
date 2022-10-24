#include <stdio.h>


int main()
{
    int c;
    double blanks = 0, tabs = 0, newlines = 0;

    while ((c = getchar()) != EOF)
        
        switch (c) {
            case ' ': ++blanks; break;
            case '\t': ++tabs; break;
            case '\n': ++newlines; break;
        }

    printf("\nBlanks: %.0f\nTabs: %.0f\nNewLines: %.0f\n", blanks, tabs, newlines);

    return 0;
}

