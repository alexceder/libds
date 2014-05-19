#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"

void _vector_auto_resize(vector *v) {
    v->capacity = 1 << ++v->capacity_power;
    v->values = realloc(v->values, sizeof(char *)*v->capacity);
}

vector *vector_create() {
    vector *v = malloc(sizeof(vector));
    v->size = 0;
    v->capacity_power = 0;
    v->capacity = 1 << v->capacity_power;
    v->values = calloc(v->capacity, sizeof(char *));

    return v;
}

void vector_destroy(vector *v) {
    vector_clear(v);
    free(v->values);
    free(v);
}

size_t vector_size(vector *v) {
    return v->size;
}

size_t vector_capacity(vector *v) {
    return v->capacity;
}

int vector_is_empty(vector *v) {
    return v->size == 0;
}

int vector_resize(vector *v, size_t n) {
    if (n < v->size) {
        for ( ; v->size > n; ) {
            free(v->values[--v->size]);
        }
    }

    v->capacity_power = (int) (log10(n) / log10(2));
    v->capacity = n;
    v->values = realloc(v->values, sizeof(char *)*v->capacity);

    return 1;
}

int vector_shrink_to_fit(vector *v) {
    v->capacity_power = (int) (log10(v->size) / log10(2));
    v->capacity = v->size;
    v->values = realloc(v->values, sizeof(char *)*v->capacity);
    return 1;
}

char *vector_get(vector *v, size_t i) {
    if (i >= v->size)
        return NULL;

    return v->values[i];
}

char *vector_get_front(vector *v) {
    if (0 == v->size)
        return NULL;

    return v->values[0];
}

char *vector_get_back(vector *v) {
    if (0 == v->size)
        return NULL;

    return v->values[v->size - 1];
}

size_t vector_set(vector *v, size_t i, char *value) {
    if (i >= v->size)
        return 0;

    free(v->values[i]);
    v->values[i] = strdup(value);
    return 1;
}

void vector_push(vector *v, char *value) {
    if (v->size >= v->capacity) {
        _vector_auto_resize(v);
    }

    v->values[v->size++] = strdup(value);
}

void vector_pop(vector *v) {
    free(v->values[--v->size]);
}

void vector_insert(vector *v, size_t pos, char *value) {
    size_t i = pos;

    if (v->size >= v->capacity) {
        /* TODO insert_after: you might want to implement a way to reallocating
         * memory and then moving it back or forth depending on where the insert is.
         * This might be able to work with memset() or some other function. */
        _vector_auto_resize(v);
    }

    for ( ; i < v->size; ++i) {
        v->values[i] = v->values[i + 1];
    }

    v->values[pos] = value;
}

size_t vector_erase(vector *v, size_t i) {
    size_t n;

    if (i >= v->size)
        return 0;

    free(v->values[i]);
    v->size--;
    for (n = i; n < v->size; ++n) {
        v->values[n] = v->values[n+1];
    }

    return 1;
}

void vector_swap(vector *v, size_t a, size_t b) {
    char *temp;

    if (a >= v->size || b >= v->size)
        return;

    temp = v->values[a];
    v->values[a] = v->values[b];
    v->values[b] = temp;
}

void vector_clear(vector *v) {
    size_t i;

    for (i = 0 ; i < v->size; ++i) {
        free(v->values[i]);
    }

    v->size = 0;
}

char *vector_dump(vector *v) {
    char *buffer;
    size_t i;
    size_t num_chars = 0;

    /* calculate the number of bytes to allocate */
    for (i = 0; i < v->size; ++i) {
        num_chars += strlen(v->values[i]) + 1;
    }

    buffer = malloc(sizeof(char)*(4+num_chars));

    /* start the dumping */
    strcpy(buffer, "{");
    for (i = 0; i < v->size; ++i) {
        strcat(buffer, " ");
        strcat(buffer, v->values[i]);
    }
    strcat(buffer, " }");

    return buffer;
}
