#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flist.h"

#define loop_flist for ( ; NULL != current->next; current = current->next)

flnode *_flnode_create(char *value) {
    flnode *n = malloc(sizeof(flnode));
    n->next = NULL;
    if (value) {
        n->value = malloc(sizeof(char)*(strlen(value)+1));
        strcpy(n->value, value);
    } else {
        n->value = NULL;
    }

    return n;
}

void _flnode_destroy(flnode *ln) {
    free(ln->value);
    free(ln);
}

flist *flist_create() {
    flnode *root = _flnode_create(NULL);
    flist *l = malloc(sizeof(flist));
    l->root = root;
    l->size = 0;

    return l;
}

void flist_destroy(flist *l) {
    flist_clear(l);
    _flnode_destroy(l->root);
    free(l);
}

size_t flist_size(flist *l) {
    return l->size;
}

flnode *flist_insert(flist *l, char *value) {
    flnode *current = l->root;

    loop_flist {
        if (strcmp(current->next->value, value) > 0) {
            flnode *temp = current->next;
            current->next = _flnode_create(value);
            current->next->next = temp;
            l->size++;
            return current->next;
        }
    }

    current->next = _flnode_create(value);
    l->size++;
    return current->next;
}

void flist_clear(flist *l) {
    flnode *current = l->root;
    flnode *temp;

    while (NULL != current->next) {
        temp = current->next;
        _flnode_destroy(current);
        current = temp;
        l->size--;
    }

    l->root = current;
}

int flist_value_exists(flist *l, char *value) {
    flnode *current = l->root;

    loop_flist {
        if (0 == strcmp(current->next->value, value)) {
            return 1;
        }
    }

    return 0;
}

char *flist_dump(flist *l) {
    flnode *current = l->root;
    char *buffer;
    size_t num_chars = 0;

    /* calculate the number of bytes to allocate */
    loop_flist {
        num_chars += strlen(current->next->value);
    }

    buffer = malloc(sizeof(char)*(4+2*num_chars));

    /* reset the pointer and start dumping */
    current = l->root;

    strcpy(buffer, "{");
    loop_flist {
        strcat(buffer, " ");
        strcat(buffer, current->next->value);
    }
    strcat(buffer, " }");

    return buffer;
}
