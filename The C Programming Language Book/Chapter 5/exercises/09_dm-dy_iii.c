#include <stdio.h>
#include <stdlib.h>

static const char daytab[2][13] = {
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
};

#define isleap(year) (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)


/* day_of_year: set day of year from month & day. return 0 if error */
int day_of_year(int year, int month, int day)
{
    if (month < 0 || month > 12)
        return 0;

    const char *tab = *(daytab + isleap(year));
    if (day < 1 || day > *(tab + month))
        return 0;

    for (month--; month > 0; month--)
        day += *tab++;

    return day;
}


/* month_day: set month-day from day of year. return 1 if error */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
    unsigned short leap = isleap(year);

    if (yearday < 1 || yearday > 365 + leap)
        return 1;

    const char *tab = *(daytab + leap);
    for (*pmonth = 1; yearday > *tab; (*pmonth)++, tab++)
        yearday -= *tab;

    *pday = yearday;

    return 0;
}


int read_date(const char s[], int *year, int *month, int *day);

#define _ERR() fprintf(stderr, "\033[31m""Error: Invalid date!\033[m\n")
#define CHECK_DAY(day) { int d = day; \
    if (d) printf("%d\n", d); \
    else { _ERR(); return EXIT_FAILURE; } }
#define CHECK_MONTHDAY(err) { \
    if (err) { _ERR(); return EXIT_FAILURE; } \
    else printf("m%d/d%d\n", month, day); }


/* Rewrite the routines day_of_year and month_day with pointers instead of indexing. */
int main(int argc, char const *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "\033[31m" "Error: Expects (year, month, day) or "
                "(year, day of year) integers as arguments.\n" "Or a single string in "
                "the formats dXX/mXX/yXXXX, XXX:yXXXX or variations." "\n\033[m\n");
        return EXIT_FAILURE;
    }
    else if (argc == 2) {
        int year, month, day;

        if (read_date(argv[1], &year, &month, &day)) {
            if (month)
                CHECK_DAY(day_of_year(year, month, day))
            else
                CHECK_MONTHDAY(month_day(year, day, &month, &day))
        }
        else
            fprintf(stderr, "\033[31m""Error: Invalid date format!\033[m\n");
    }
    else if (argc == 3) {
        int month, day;
        CHECK_MONTHDAY(month_day(atoi(argv[1]), atoi(argv[2]), &month, &day))
    }
    else
        CHECK_DAY(day_of_year(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])))

    return EXIT_SUCCESS;
}


#include <ctype.h>

int atoi_(const char *(*s));


/* read date from string in the formats: dXX/mXX/yXXXX, XXX:yXXXX and variants.
 * return 0 if invalid or incomplete. if no month is specified assigns it to 0 */
int read_date(const char s[], int *year, int *month, int *day)
{
    unsigned short fd, fm, fy, fyd; /* found: day, month, year, year'day */
    fd = fm = fy = fyd = 0;
    *month = 0;

    while (*s != '\0') {
        while (isspace(*s))
            s++; /* ignore blank space */

        switch (*s++) {
            case 'd':
            case 'D': {
                if (fd || fyd || fy == 3)
                    return 0;
                else
                    *day = atoi_(&s);

                if (*s == '/')
                    s++; /* ignores separator */
            } break;
            case 'm':
            case 'M': {
                if (fm || fyd || fy == 3)
                    return 0;
                else
                    *month = atoi_(&s);

                if (*s == '/')
                    s++; /* ignores separator */

                fm = 1;
            } break;
            case 'y':
            case 'Y': {
                if (fy)
                    return 0;
                else
                    *year = atoi_(&s);

                fy = 1;
                if (*s == '/') {
                    if (fyd)
                        return 0; /* invalid separator to year'day */
                    s++; /* ignores separator */
                    fy = 2; /* signal to using year-month-day format */
                }
                else if (*s == ':') {
                    if (fm || fd)
                        return 0; /* invalid separator to year-month-day */
                    s++; /* ignores separator */
                    fy = 3; /* signal to using year'day format */
                }
            }; break;
            default: {
                s--; /* re-shift s */
                if (*s >= '0' && *s <= '9') { /* read number as day of year */
                    if (fyd || fm || fd || fy == 2)
                        return 0;
                    else
                        *day = atoi_(&s);

                    if (*s == ':')
                        s++; /* ignores separator */

                    fyd = 1;
                }
                else
                    return 0;
            } break;
        }
    }

    return 1;
}


/* atoi_: convert s to integer: specialized version: shifts the string */
int atoi_(const char *(*s))
{
	int n, sign;

    while (isspace(**s))
        (*s)++; /* skip white space */

    while (isdigit(**s) && **s == '0')
        (*s)++; /* skip leading zeros */

	for (n = 0; isdigit(**s); (*s)++) /* convert integer part */
		n = 10 * n + (**s - '0');

    while (isspace(**s))
        (*s)++; /* skip white space */

	return n;
}
