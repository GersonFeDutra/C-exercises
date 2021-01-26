#include <stdio.h>

#define IN  1 /* inside a word */
#define OUT 0 /* outside a word */


/* count lines, words, and characters in input */
int main()
{
    int c, nl, nw, nc, state = OUT;
    nl = nw = nc = 0;

    while ((c = getchar()) != EOF) {
        ++nc;

        if (c == ' ' || c == '\n' || c == '\t') {

            if (c == '\n')
                ++nl;
            
            state = OUT;
        }
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("Lines: %d\nWords: %d\nCharacters: %d\n", nl, nw, nc);
    
    return 0;
}
