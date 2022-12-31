/* Common macros */

#define forever for(;;) /* infinite loop */
#define max(A, B) (((A) > (B)) ? (A) : (B))

// #define square(X) X * X /* Wrong: this may causes precedence issues */
#define square(X) (X) * (X)

/* debug-print the expression statement and value */
#define dprint(expr) printf(#expr " = %g\n", expr)

#define paste(front, back) front ## back /* concatenates front with back */


/* Conditional inclusion */
#if SYSTEM == SYSV
    #define HDR "sysv.h"
#elif SYSTEM == BSD
    #define HDR "bsd.h"
#elif SYSTEM == MSDOS
    #define HDR "msdos.h"
#endif

/* using ifdef and ifndef */
#ifndef HDR
#define HDR
/* contents of hdr.h go here */
#endif

#ifdef HDR
    // #include HDR
#endif
