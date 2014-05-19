#include <stddef.h>

#ifndef VECTOR_H
#define VECTOR_H

struct vector {
    char **values;
    size_t size;
    size_t capacity;
    size_t capacity_power;
};

typedef struct vector vector;

void _vector_auto_resize(vector *v);

/* constructor & destructor */
vector *vector_create();
void vector_destroy(vector *v);

/* capacity */
size_t vector_size(vector *v);
size_t vector_capacity(vector *v);
int vector_is_empty(vector *v);
int vector_resize(vector *v, size_t n);
int vector_shrink_to_fit(vector *v);

/* accessors */
char *vector_get(vector *v, size_t i);
char *vector_get_front(vector *v);
char *vector_get_back(vector *v);

/* modifiers */
size_t vector_set(vector *v, size_t i, char *value);
void vector_push(vector *v, char *value);
void vector_pop(vector *v);
void vector_insert(vector *v, size_t pos, char *value);
size_t vector_erase(vector *v, size_t i);
void vector_swap(vector *v, size_t a, size_t b);
void vector_clear(vector *v);

/* helpers */
char *vector_dump(vector *v);

#endif /* VECTOR_H */
