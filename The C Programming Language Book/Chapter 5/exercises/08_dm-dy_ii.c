#include <stdio.h>
#include <stdlib.h>

static char daytab[2][13] = {
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
};

#define isleap(year) year % 4 == 0 && year % 100 != 0 || year % 400 == 0


/* day_of_year: set day of year from month & day. return 0 if error */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (month < 0 || month > 12)
        return 0;

    leap = isleap(year);
    if (day < 1 || day > daytab[leap][month])
        return 0;

    for (i = 1; i < month; i++)
        day += daytab[leap][i];

    return day;
}


/* month_day: set month-day from day of year. return 1 if error */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = isleap(year);
    if (yearday < 1 || yearday > 365 + leap)
        return 1;

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];

    *pmonth = i;
    *pday = yearday;

    return 0;
}


#define ERR() fprintf(stderr, "\033[31m""Error: Invalid date!\033[m\n")
/* There was no erro checking in day_of_year or month_day. Remedy this effect. */
int main(int argc, char const *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "\033[31m""Error: Expects (year, month, day) or "
                "(year, day of year) integers as arguments.\n\033[m\n");
        return EXIT_FAILURE;
    }
    else if (argc == 3) {
        int month, day;

        if (month_day(atoi(argv[1]), atoi(argv[2]), &month, &day)) {
            ERR();
            return EXIT_FAILURE;
        }
        else
            printf("m%d/d%d\n", month, day);
    }
    else {
        int day = day_of_year(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

        if (day)
            printf("d%d\n", day);
        else {
            ERR();
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
