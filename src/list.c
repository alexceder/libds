#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

lnode *_lnode_create(char *value) {
    lnode *n = malloc(sizeof(lnode));

    n->next = NULL;

    if (value) {
        n->value = strdup(value);
    } else {
        n->value = NULL;
    }

    return n;
}

void _lnode_destroy(lnode *n) {
    free(n->value);
    free(n);
}

list_iter list_iter_next(list_iter lit) {
    lit.current = lit.current->next;
    return lit;
}

list_iter list_iter_prev(list_iter lit) {
    lit.current = lit.current->prev;
    return lit;
}

lnode *list_iter_node(list_iter lit) {
    return lit.current;
}

char *list_iter_value(list_iter lit) {
    return lit.current->value;
}

list_iter list_iter_front(list *l) {
    list_iter lit;
    lit.current = l->front->next;
    return lit;
}

list_iter list_iter_back(list *l) {
    list_iter lit;
    lit.current = l->back->prev;
    return lit;
}

int list_iter_equal(list_iter first, list_iter second) {
    return list_iter_node(first) == list_iter_node(second);
}

list *list_create() {
    list *l = malloc(sizeof(list));
    lnode *front = _lnode_create(NULL);
    lnode *back = _lnode_create(NULL);

    l->front = front;
    l->back = back;
    l->size = 0;

    return l;
}

void list_destroy(list *l) {
    list_clear(l);
    _lnode_destroy(l->front);
    _lnode_destroy(l->back);
    free(l);
}

int list_is_empty(list *l) {
    return 0 == l->size;
}

size_t list_size(list *l) {
    return l->size;
}

char *list_front(list *l) {
    return l->front->next->value;
}

char *list_back(list *l) {
    return l->back->next->value;
}

void list_insert(list *l, list_iter lit, char *value) {
    lnode *current = list_iter_node(lit);
    lnode *temp_prev = current->prev;

    current->prev = _lnode_create(value);
    current->prev->prev = temp_prev;
    current->prev->next = current->next;
    current->next->prev = current->prev;

    l->size++;
}

void list_insert_after(list *l, list_iter lit, char *value) {
}

void list_push_front(list *l, char *value) {
}

void list_pop_front(list *l) {
}

void list_push_back(list *l, char *value) {
}

void list_pop_back(list *l) {
}

void list_erase(list *l, list_iter lit) {
}

void list_clear(list *l) {
    list_iter lit = list_iter_front(l);
    list_iter lit_back = list_iter_back(l);
    list_iter temp;

    for ( ; list_iter_equal(lit, lit_back); ) {
        temp = list_iter_next(lit);
        _lnode_destroy(list_iter_node(lit));
        lit = temp;
    }

    l->size = 0;
    l->front = l->back;
}

char *list_dump(list *l) {
    list_iter lit = list_iter_front(l);
    list_iter lit_back = list_iter_back(l);
    char *buffer;
    size_t num_chars = 0;

    /* calculate the number of bytes to allocate */
    for ( ; list_iter_equal(lit, lit_back); lit = list_iter_next(lit)) {
        num_chars += strlen(list_iter_value(lit) + 1); /* 1 for the space */
    }

    buffer = malloc(sizeof(char)*(4+num_chars));

    /* reset the iterator and start dumping */
    lit = list_iter_front(l);

    strcpy(buffer, "{");
    for ( ; list_iter_equal(lit, lit_back); lit = list_iter_next(lit)) {
        strcat(buffer, " ");
        strcat(buffer, list_iter_value(list_iter_next(lit)));
    }
    strcat(buffer, " }");

    return buffer;
}
