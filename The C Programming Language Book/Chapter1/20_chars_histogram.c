#include <stdio.h>


int main()
{
    const ALPHASIZE = 'Z' - 'A' + 1;
    const ALL_PHASIZE = 2 * ALPHASIZE;
    const SIZE = ALL_PHASIZE + ('9' - '0' + 1);

    void printline(int);
    int c, i, j;
    int histo[SIZE];

    for (i = 0; i < SIZE; ++i)
        histo[i] = 0;
    
    /* Reads the text stream input */
    while ((c = getchar()) != EOF)
    {
        if (c >= 'A' && c <= 'Z')
            ++histo[c - 'A'];
        
        else if (c >= 'a' && c <= 'z')
            ++histo[c + ALPHASIZE - 'a'];
        
        else if (c >= '0' && c <= '9')
            ++histo[c + ALL_PHASIZE - '0'];
    }
    
    /* Prints the histogram */
    for (i = 0; i < SIZE; ++i)

        if (histo[i] > 0)

            if (i >= 0 && i < ALPHASIZE) {
                printf("%c:", 'A' + i);
                printline(histo[i]);
            }
            
            else if (i >= ALPHASIZE && i < ALL_PHASIZE) {
                printf("%c:", 'a' + i - ALPHASIZE);
                printline(histo[i]);
            }
            else {
                printf("%c:", '0' + i - ALL_PHASIZE);
                printline(histo[i]);
            }
    
    return 0;
}


void printline(int size)
{
    int i;

    for (i = 0; i < size; ++i)
        printf(" -");
    
    printf("\n");
}
