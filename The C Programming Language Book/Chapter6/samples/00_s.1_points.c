#include <stdio.h>
#include <stdlib.h>

#define pr_point(p) printf(#p ": (%d, %d)\n", p.x, p.y)


int main(void)
{
    struct point {
        int x;
        int y;
    } x, y, z;

    struct point pt;
    struct point maxpt = { 320, 200 };
    pr_point(maxpt);

    double dist, sqrt(double);
    dist = sqrt((double) pt.x * pt.y + (double) pt.y * pt.y);

    return EXIT_SUCCESS;
}
