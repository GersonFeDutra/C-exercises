#include <stdio.h>
#include <stdlib.h>


/* cat: concatenate files, version 2 */
int main(int argc, char const *argv[])
{
    FILE *fp;
    void filecopy(FILE *, FILE *);
    const char *prog = argv[0]; /* program name for errors */

    if (argc == 1) /* no args: copy standard input */
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "\033[31m""%s: can't open %s""\033[31m\n",
                        prog, *argv);
                exit(EXIT_FAILURE);
            }
            else {
                filecopy(fp, stdout);
                fclose(fp);
            }
    if (ferror(stdout)) {
        fprintf(stderr, "\033[31m""%s: error writing stdout\n", prog);
        exit(2);
    }


    return EXIT_SUCCESS;
}


/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;

    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}
