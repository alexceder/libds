#include <stddef.h>

#ifndef LIST_H
#define LIST_H

struct lnode_s;
struct list_s;
struct list_iter_s;

typedef struct lnode_s lnode;
typedef struct list_s list;
typedef struct list_iter_s list_iter;

struct lnode_s {
    char *value;
    lnode *next;
    lnode *prev;
};

lnode *_lnode_create(char *value);
void _lnode_destroy(lnode *that);

struct list_iter {
    lnode *current;
};

/* iterator methods */
list_iter list_iter_next(list_iter lit);
list_iter list_iter_prev(list_iter lit);
lnode *list_iter_node(list_iter lit);
char *list_iter_value(list_iter lit);
list_iter list_iter_front(list *l);
list_iter list_iter_back(list *l);
int list_iter_equal(list_iter first, list_iter second);

struct list {
    lnode *front;
    lnode *back;
    size_t size;
};

/* constructor & destructor */
list *list_create();
void list_destroy(list *l);

/* capacity */
int list_is_empty(list *l);
size_t list_size(list *l);

/* accessors */
char *list_front(list *l);
char *list_back(list *l);

/* modifiers */
void list_insert(list *l, list_iter lit, char *value);
void list_insert_after(list *l, list_iter lit, char *value);
void list_push_front(list *l, char *value);
void list_pop_front(list *l);
void list_push_back(list *l, char *value);
void list_pop_back(list *l);
void list_erase(list *l, list_iter lit);
void list_clear(list *l);

/* helpers */
char *list_dump(list *l);

#endif /* LIST_H */
