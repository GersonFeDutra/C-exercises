#include <stdio.h>

/* interchanges two arguments of type t */
#define swap(t, x, y) t _tmp = x; x = y; y = _tmp;

/* debug-print the expression statement and value */
#define dprint(expr) printf(#expr " = %d\n", expr)
/* Define a macro swap(t,x,y) that interchanges two arguments of type t */
int main(void)
{
    int x = 1;
    int y = 2;

    dprint(x);
    dprint(y);
    swap(int, x, y);
    dprint(x);
    dprint(y);
}
