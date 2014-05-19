#include <stddef.h>

#ifndef SLIST_H
#define SLIST_H

struct lnode;
struct list;

typedef struct lnode lnode;
typedef struct list list;

struct lnode {
    char *value;
    lnode *next;
};

lnode *_lnode_create(char *value);
void _lnode_destroy(lnode *that);

struct list {
    lnode *root;
    size_t size;
};

/* constructor & destructor */
list *list_create();
void list_destroy(list *l);

/* capacity */
/*int list_is_empty(list *l);*/
size_t list_size(list *l);

/* accessors */
/*char *list_front(list *l);*/
/*char *list_back(list *l);*/

/* modifiers */
lnode *list_insert(list *l, char  *value); /* insert_ordered */
void list_clear(list *l);
/* functions below should be implemented at some time
 * might add an iterator type to help some things */
/*void list_push_front(list *l, char *value);*/
/*void list_pop_front(list *l, char *value);*/
/*void list_insert_at(list *l, size_t i, char  *value);*/
/*void list_insert_after(list *l, char *after, char  *value);*/
/*void list_erase_at(list *l, size_t i);*/
/* the following two should be implemented with pointers/iterators */
/*void list_erase_range(list *l, size_t start, size_t end);*/
/*void list_swap(list *l, size_t start, size_t end);*/

/* operations */
int list_value_exists(list *l, char *value); /* not needed */

/* helpers */
char *list_dump(list *l);

#endif /* SLIST_H */
