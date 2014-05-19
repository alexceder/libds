#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "bheap.h"

void _heap_build(heap *h) {
    size_t i = heap_size(h)/2;

    for ( ; i > 0; --i)
        _heap_percolate_down(h, i);
}

void _heap_percolate_down(heap *h, size_t i) {
    size_t child;
    vector *v = h->values;
    char *temp = vector_get(v, i);

    for ( ; LEFT_CHILD(i) <= heap_size(h); i = child) {
        child = LEFT_CHILD(i);

        if (child != heap_size(h) &&
            strcmp(vector_get(v, child+1), vector_get(v, child)) HEAP_COMPARE_INV 0)
            ++child;

        if (strcmp(vector_get(v, child), temp) HEAP_COMPARE_INV 0) {
            vector_swap(v, i, child);
        } else {
            break;
        }
    }
}

heap *heap_create() {
    heap *h = malloc(sizeof(heap));
    h->values = vector_create();
    vector_push(h->values, "(dummy)");
    return h;
}

heap *heap_create_from_array(char **arr, size_t n) {
    heap *h = heap_create();
    size_t i = 0;

    for ( ; i < n; ++i)
        vector_push(h->values, arr[i]);

    _heap_build(h);

    return h;
}

void heap_insert(heap *h, char *value) {
    size_t i = heap_size(h) + 1;

    vector_push(h->values, value);

    for ( ; strcmp(vector_get(h->values, PARENT(i)), value) HEAP_COMPARE 0; i = PARENT(i)) {
        vector_swap(h->values, i, PARENT(i));
    }
}

void heap_pop(heap *h) {
    vector_swap(h->values, 1, heap_size(h));
    vector_pop(h->values);
    _heap_percolate_down(h, 1);
}

size_t heap_size(heap *h) {
    return h->values->size - 1;
}

void heap_clean(heap *h) {
    vector_clear(h->values);
}

void heap_destroy(heap *h) {
    vector_destroy(h->values);
    free(h);
}

char *heap_dump(heap *h) {
    char *buffer;
    vector *v = h->values;
    size_t i, x, y, index, height;

    buffer = malloc(sizeof(char)*512);

    height = (int) ceil(log2(v->size));

    strcpy(buffer, "");

    index = 0;
    for (i = 0; i < height; ++i) {
        for (x = 0; x < pow(2, i) && index < heap_size(h); x++) {
            for (y = height; i < y; --y) strcat(buffer, " ");
            strcat(buffer, v->values[(index++)+1]);
        }
        strcat(buffer, "\n");
    }

    return buffer;
}
