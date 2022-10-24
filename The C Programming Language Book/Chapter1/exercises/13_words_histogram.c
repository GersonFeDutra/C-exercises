#include<stdio.h>

#define IN  1 /* Inside a word */
#define OUT 0 /* Outside a word */
#define COLUMNS 50 /* basicaly the max number of columns in the histogram. */


/*
 * Write a program to print a histogram of the frequencies of the length of words in its input.
 * Horizontal version
 */
int main()
{
    int c, i, nwords = 0, count = 0, state = OUT;
    int nletters[COLUMNS]; 

    /* The array must be a fixed size, that was a "C problem" I couldn't solve for now */
    for (i = 0; i < COLUMNS; ++i)
        nletters[i] = 0;
    
    /* Populating the array with character counts of the typed words */
    while ((c = getchar()) != EOF || nwords == COLUMNS) {

        if (c == '\n' || c == '\t' || c == ' ' || c == '"') {

            if(state != OUT)
                state = OUT;
        }
        //else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        else {

            if (state == OUT) {

                count = OUT;
                ++nwords;
                state = IN;
            }
            ++count;
            nletters[nwords - 1] = count;
        }
    }

    /* Printing the Histogram Finally */ 
    for (i = 0; i < nwords; ++i) {

        for (count = 0; count < nletters[i]; ++count)
            printf("-");

        printf("\n");
    }

    return 0;
}

