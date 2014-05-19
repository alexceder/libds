#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "slist.h"

#define loop_list for ( ; NULL != current->next; current = current->next)

lnode *_lnode_create(char *value) {
    lnode *n = malloc(sizeof(lnode));
    n->next = NULL;
    if (value) {
        n->value = malloc(sizeof(char)*(strlen(value)+1));
        strcpy(n->value, value);
    } else {
        n->value = NULL;
    }

    return n;
}

void _lnode_destroy(lnode *ln) {
    free(ln->value);
    free(ln);
}

list *list_create() {
    lnode *root = _lnode_create(NULL);
    list *l = malloc(sizeof(list));
    l->root = root;
    l->size = 0;

    return l;
}

void list_destroy(list *l) {
    list_clear(l);
    _lnode_destroy(l->root);
    free(l);
}

size_t list_size(list *l) {
    return l->size;
}

lnode *list_insert(list *l, char *value) {
    lnode *current = l->root;

    loop_list {
        if (strcmp(current->next->value, value) > 0) {
            lnode *temp = current->next;
            current->next = _lnode_create(value);
            current->next->next = temp;
            l->size++;
            return current->next;
        }
    }

    current->next = _lnode_create(value);
    l->size++;
    return current->next;
}

void list_clear(list *l) {
    lnode *current = l->root;
    lnode *temp;

    while (NULL != current->next) {
        temp = current->next;
        _lnode_destroy(current);
        current = temp;
        l->size--;
    }

    l->root = current;
}

int list_value_exists(list *l, char *value) {
    lnode *current = l->root;

    loop_list {
        if (0 == strcmp(current->next->value, value)) {
            return 1;
        }
    }

    return 0;
}

char *list_dump(list *l) {
    lnode *current = l->root;
    char *buffer;
    size_t num_chars = 0;

    /* calculate the number of bytes to allocate */
    loop_list {
        num_chars += strlen(current->next->value);
    }

    buffer = malloc(sizeof(char)*(4+2*num_chars));

    /* reset the pointer and start dumping */
    current = l->root;

    strcpy(buffer, "{");
    loop_list {
        strcat(buffer, " ");
        strcat(buffer, current->next->value);
    }
    strcat(buffer, " }");

    return buffer;
}
