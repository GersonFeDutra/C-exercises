#include <stdio.h>
#include <stdlib.h>


int get_line(char s[], int lim);

int main(void)
{
    int day, month, year;
    char line[250], monthname[20];

    while (get_line(line, sizeof(line)) > 0)
        if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
            printf("\033[32m""valid: %s\n""\033[m", line);   /* 25 December 1988 form */
        else if (sscanf(line, "%d/%d/%d", &year, &month, &day) == 3)
            printf("\033[32m""valid: %s\n""\033[m", line);   /* yyyy/mm/dd form */
        else
            printf("\033[31m""invalid: %s\n""\033[m", line); /* invalid form */

    return EXIT_SUCCESS;
}

/* Read a line into string `s`, return length. */
int get_line(char s[], int lim)
{
	int c, i;

	for (i = 0; (i < lim - 1) && ((c = getchar()) != EOF) && (c != '\n'); ++i)
		s[i] = c;

	if (c == '\n')
		s[i++] = c;

	s[i] = '\0';

	return i;
}
