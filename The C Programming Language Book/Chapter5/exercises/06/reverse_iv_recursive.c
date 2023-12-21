#include <stdio.h>
#include <stdlib.h>

static char *_t_reverse;

/* auxiliar recursive method of reverse */
static char *_reverse(char *s)
{
    if (*s == '\0')
        return s;

    char *ls = _reverse(s + 1); /* last swapped s */

    if (s != _t_reverse && _t_reverse != ls) { /* swap */
        char c = *s;
        *s = *_t_reverse;
        *_t_reverse = c;

        _t_reverse++; /* next */
    }
    else
        return ls; /* propagate the cancellation condition at the return */

    return s;
}


/* reverse: reverse string s in place: recursive pointer version */
void reverse(char *s)
{
    _t_reverse = s;
    if (*s != '\0') /* can only swap if not empty */
        _reverse(s);
}


int main(int argc, char const *argv[])
{
    int len = 255;

    if (argc == 2)
        len = atoi(argv[2]);
    else
        fprintf(stderr,
                "\033[33mWarning! Buffer size not informed, using default (%d).\033[m\n", len);

    char s[len];
    int i, c;

    for (i = 0; (c = getchar()) != EOF && i < len - 1; ++i)
        s[i] = c;
    s[i] = '\0';

    reverse(s);

    printf("%s\n", s);

    return EXIT_SUCCESS;
}
