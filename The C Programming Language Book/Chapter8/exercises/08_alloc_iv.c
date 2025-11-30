#include <unistd.h> // sbrk
#include <limits.h>
#include <stdint.h>

typedef long Align; /* for alignment to long boundary */

union header {
    struct {
        union header *ptr; /* next block if on free list */
        unsigned size;     /* size of this block */
    } s;
    Align x; /* force alignment of blocks */
};

typedef union header Header;


static Header base;     /* empty list to get started */
static Header *freep = NULL;   /* start of free list */

/* malloc: general-purpose storage allocator */
void *_malloc(unsigned nbytes)
{
    if (nbytes == 0)
        return NULL;

    /* Convert bytes to header units, with overflow check */
    if (nbytes > UINT_MAX - sizeof(Header))
        return NULL; /* unreasonable request */

    Header *p, *prevp;
    Header *_morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) { /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) { /* big enough */
            if (p->s.size == nunits)  /* exactly */
                prevp->s.ptr = p->s.ptr;
            else { /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *) (p + 1);
        }
        if (p == freep) /* wrapped around free list */
            if ((p = _morecore(nunits)) == NULL)
                return NULL; /* none left */
    }
}

void *_calloc(unsigned nbytes, unsigned size)
{
    unsigned len = nbytes * size;
    void *p = _malloc(len);
    if (p)
        for (char *q = p; q < (char *)(p) + len; q++)
            *q = 0;
    return p;
}


/* free: put block ap in free list */
void _free(void *ap)
{
    if (ap == NULL)
        return;
    /* Must be aligned like a Header */
    if ((uintptr_t)ap % sizeof(Header) != 0)
        return; /* invalid pointer */

    Header *bp, *p;
    bp = (Header *) ap - 1; /* point to block header */

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; /* freed block at start or end of arena */

    /* Block size must be >= 1 */
    if (bp->s.size < 1)
        return; /* corrupt header */

    if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp) { /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;

    freep = p;
}

int bfree(void *ap, unsigned nbytes)
{
    Header *bp, *p;
    unsigned nunits;

    if (ap == NULL || nbytes == 0)
        return -1;

    if ((uintptr_t)ap % sizeof(Header) != 0)
        return -1; /* must be aligned like a Header */

    /* convert bytes → header units, include space for header */
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if (nunits < 2)
        return -1; /* must hold at least header + 1 unit */

    bp = (Header *)ap; /* point to block header */
    bp->s.size = nunits;

    /* 1. free list not initialized */
    if (freep == NULL) {
        /* create a self-pointing circular list */
        freep = bp;
        freep->s.ptr = freep;
        return 0;
    }

    /* 2. normal insertion into free list */
    p = freep;
    while (!(bp > p && bp < p->s.ptr)) {  /* look for place to insert */

        /* special case: at one end or the other */
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;

        p = p->s.ptr;
    }

    /* coalesce with upper neighbor */
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }

    /* coalesce with lower neighbor */
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }

    return 0;
}


#define NALLOC 8192 /* minimum #units to request */

/* morecore: ask system for more memory */
Header *_morecore(unsigned nu)
{
    char *cp;
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) - 1) /* no space at all */
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    _free((void *)(up + 1));

    return freep;
}


#pragma region Main Program
#include <stdio.h>
#include <string.h>


/** Write a routine bfree(p, n) that will free an arbitrary block p of n
 * characters into the free list maintained by malloc and free. By using bfree,
 * a user can add a static or external array to the free list at any time.
 **/
int main()
{
    static char external[100];
    bfree(external, sizeof(external));

    char *p = (char *)_calloc(50, sizeof(char));
    if (p == NULL) {
        fprintf(stderr, "\033[31m""_calloc failed""\033[m\n");
        return 1;
    }
    sprintf(p, "\033[32m""Hello 🌍!""\033[0m");
    printf("%s\n", p);
    _free(p);

    return 0;
}
#pragma endregion
