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


// TODO
/** malloc accepts a size request without checking its plausibility;
 * free believes that the block it is asked to free contains a valid size field.
 * Improve these routines so they take more pains with error checking.
 **/
int main()
{
    char *p = (char *)_calloc(100, sizeof(char));
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
