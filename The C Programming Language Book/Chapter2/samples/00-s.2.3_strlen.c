#include <stdio.h>


/* strlen: return length of s */
int strlen(const char s[])
{
    int i = 0;

    while (s[i] != '\0')
        ++i;

    return i;
}


int main(int argc, char const *argv[])
{
    char string[] = "Hello World";

    printf("\"%s\" length: %d.\n", string, strlen(string));

    return 0;
}
