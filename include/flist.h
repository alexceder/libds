#include <stddef.h>

#ifndef FLIST_H
#define FLIST_H

struct flnode;
struct flist;

typedef struct flnode_s flnode;
typedef struct flist_s flist;

struct flnode_s {
    char *value;
    flnode *next;
};

flnode *_flnode_create(char *value);
void _flnode_destroy(flnode *that);

struct flist_s {
    flnode *root;
    size_t size;
};

/* constructor & destructor */
flist *flist_create();
void flist_destroy(flist *l);

/* capacity */
/*int flist_is_empty(flist *l);*/
size_t flist_size(flist *l);

/* accessors */
/*char *flist_front(flist *l);*/
/*char *flist_back(flist *l);*/

/* modifiers */
flnode *flist_insert(flist *l, char *value); /* insert_ordered */
void flist_clear(flist *l);
/* functions below should be implemented at some time
 * might add an iterator type to help some things */
/*void flist_push_front(flist *l, char *value);*/
/*void flist_pop_front(flist *l, char *value);*/
/*void flist_insert_at(flist *l, size_t i, char  *value);*/
/*void flist_insert_after(flist *l, char *after, char  *value);*/
/*void flist_erase_at(flist *l, size_t i);*/
/* the following two should be implemented with pointers/iterators */
/*void flist_erase_range(flist *l, size_t start, size_t end);*/
/*void flist_swap(flist *l, size_t start, size_t end);*/

/* operations */
int flist_value_exists(flist *l, char *value); /* not needed */

/* helpers */
char *flist_dump(flist *l);

#endif /* FLIST_H */
