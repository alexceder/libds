#include <stddef.h>
#include "vector.h"

#ifndef BHEAP_H
#define BHEAP_H

#define HEAP_COMPARE >
#define HEAP_COMPARE_INV <

#define LEFT_CHILD(i) (2*i)
#define RIGHT_CHILD(i) (2*i+1)
#define PARENT(i) (i/2)

struct heap {
    vector *values;
};

typedef struct heap heap;

void _heap_build(heap *h);
void _heap_percolate_down(heap *h, size_t i);

heap *heap_create();
heap *heap_create_from_array(char **arr, size_t n);
void heap_insert(heap *h, char *value);
void heap_pop(heap *h);
size_t heap_size(heap *h);
void heap_clean(heap *h);
void heap_destroy(heap *h);
char *heap_dump(heap *h);

#endif /* BHEAP_H */
