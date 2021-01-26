#include<stdio.h>

#define IN  1 /* Inside a word */
#define OUT 0 /* Outside a word */
#define COLUMNS 50 /* basicaly the max number of columns in the histogram. */


main()
{
    int c, i, nwords = 0, count = 0, state = OUT;
    int nletters[COLUMNS]; 

    /* The array must be a fixed size, that was a "C problem" I couldn't solve for now */
    for (i = 0; i < 50; ++i)
        nletters[i] = 0;
    
    /* Populating the array with character counts of the typed words */
    while ((c = getchar()) != EOF) {

        if (c == '\n' || c == '\t' || c == ' ' || c == '"') {

            if(state != OUT)
                state = OUT;
        }
        else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {

            if (state == OUT) {

                count = OUT;
                ++nwords;
                state = IN;
            }
            ++count;
            nletters[nwords - 1] = count;
        }
    }
    c = OUT;

    /* Finding the character count of the longest word */
    for (i = 0; i < nwords; ++i) {

        if (c < nletters[i])
            c = nletters[i];
    }

    /* Printing the Histogram Finally */ 
    for (i = c; i > 0; --i) {

        for (count = 0; count < nwords; ++count) {

            if (nletters[count] - i < 0)
                printf("  ");
            else
                printf("- ");
        }
            printf("\n");
    }
}
