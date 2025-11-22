#include <stdio.h>
#include <stdlib.h>


/** page:
 * @brief Echo a set of files as pages.
 * Write a program to print a set of files, starting each new one on a new page,
 * with a title and a running page count for each file.
 *
 * @note Usage: ./page file1 [file2 ...]
 **/
int main(int argc, char const *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "\033[33mUsage: '%s' file1 [file2 ...]\033[m\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp;
    void filecopy(FILE *, FILE *);
    const char *prog = argv[0]; /* program name for errors */
    size_t err_count = EXIT_SUCCESS;
    size_t page_count = 0;

    while (--argc > 0)
        if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "\033[31m""%s: can't open %s""\033[31m\n",
                    prog, *argv);
            err_count += EXIT_FAILURE;
        }
        else {
            fprintf(stderr, "\033[34m");
            fflush(stderr);
            printf("%s [page %zu]\n", *argv, ++page_count);
            fflush(stdout);
            fprintf(stderr, "\033[m");
            fflush(stderr);

            filecopy(fp, stdout);
            fclose(fp);
            putchar('\n');
        }

    if (ferror(stdout)) {
        fprintf(stderr, "\033[31m""%s: error writing stdout\n", prog);
        exit(2);
    }

    return err_count;
}


/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}
