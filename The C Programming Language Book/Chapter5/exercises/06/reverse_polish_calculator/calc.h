#define MAXOF  100 /* max size of operand or operator */
#define NUMBER '0' /* Signal that a number was found */

int getop(char *);

/* Stack */
void push(double);
double pop(void);
// extras
void st_print(void);
void st_dupl(void);
void st_swap(void);
void st_clear(void);
// variables
void save(int c);
int access(int c);
