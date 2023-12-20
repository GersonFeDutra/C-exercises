#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist { /* table entry */
    struct nlist *next; /* next entry in chain */
    char *name;         /* defined name */
    char *defn;         /* replacement text */
};


int print(char *what)
{
    struct nlist *lookup(char *s);
    struct nlist *r = lookup(what);

    if (r == NULL)
		printf("\"%s\" not found!\n", what);
	else
        printf("definition: %s, name: %s\n", r->defn, r->name);
}


int main(void)
{
    struct nlist *install(char *name, char *defn);

    install("h", "hello");
    install("w", "world");
    print("h");
    print("w");
    print("hello");
    print("world");

    return EXIT_SUCCESS;
}


#define HASH_SIZE 101

static struct nlist *hashtab[HASH_SIZE]; /* pointer table */


/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;

	return hashval % HASH_SIZE;
}


struct nlist *lookup(char *);

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(* np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;

        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else /* already there */
        free((void *) np->defn); /* free previous definition */

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}


/* lookup: look for s in hash tab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np; /* found */

	return NULL; /* not found */
}
