#include <stdio.h>
#include <stdlib.h>


int name2month(char *);

int main(void)
{
    int day, year;
    char monthname[20];

    scanf("%d %s %d", &day, monthname, &year);

	int month = name2month(monthname);

	if (month)
        printf("%d/%d/%d\n", year, month, day);
    else {
		printf("%d/XX/%d\n", year, day);
		fprintf(stderr, "\033[31m""Illegal month!""\033[m\n");
    }

    return EXIT_SUCCESS;
}


int binsearch(const char *, const char *[], int);

/* name to month: return month from name */
int name2month(char *w)
{
    static const char *name[] = {
        "January",   "February", "March",    "April",
        "May",       "June",     "July",     "August",
        "September", "October",  "November", "December",
    };

    return binsearch(w, name, 12) + 1;
}


#include <string.h>
#define NOMATCH -1


/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(const char *word, const char *tab[], int n)
{
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;

		if ((cond = strcmp(word, tab[mid])) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}

	return NOMATCH; /* no match */
}
