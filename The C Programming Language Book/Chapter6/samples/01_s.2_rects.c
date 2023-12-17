#include <stdio.h>
#include <stdlib.h>

#define XMAX 1280
#define YMAX 720

#define pr_point(p) printf(#p ": (%d, %d)\n", p.x, p.y)

struct point {
    int x;
    int y;
};

struct rect {
    struct point pos, end;
} screen;


int main(void)
{
    pr_point(screen.end);

    struct point middle;
    struct point make_point(int, int);

    screen.pos = make_point(0, 0);
    screen.end = make_point(XMAX, YMAX);

    struct point origin, *pp; /* pointer to point p */

    pp = &origin;
    // printf("origin: (%d, %d)\n", (*pp).x, (*pp).y); // equivalent to below:
    printf("origin: (%d, %d)\n", pp->x, pp->y);

    struct rect r, *rp = &r;
    // these four expressions are equivalent:
    r.pos.x;
    rp->pos.x;
    (r.pos).x;
    (rp->pos).x;

    struct {
        int len;
        char *str;
    } *p, str = {3, "str"};
    p = &str;

    ++p->len; // increments len, not p
    // ++(p->len); // equivalent to above
    // printf("%d\n", p->len);

    return EXIT_SUCCESS;
}


/* make_point: make a point from x and y components */
struct point make_point(int x, int y)
{
    struct point tmp = { x, y }; // allowed?

    return tmp;
}


struct point add_points(struct point p, struct point q)
{
    p.x += q.x;
    p.y += q.y;

    return p;
}


/* ptinrect: return 1 if p in r, 0 if not */
int ptinrect(struct point p, struct rect r)
{
    return p.x >= r.pos.x && p.x < r.end.x
            && p.y >= r.pos.y && p.y < r.end.y;
}


#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))


/* canon_rect: canonicalize coordinates of rectangle */
struct rect canon_rect(struct rect r)
{
    struct rect tmp;

    tmp.pos.x = min(r.pos.x, r.end.x);
    tmp.pos.y = min(r.pos.y, r.end.y);
    tmp.end.x = max(r.pos.x, r.end.x);
    tmp.end.y = max(r.pos.y, r.end.y);

    return tmp;
}
