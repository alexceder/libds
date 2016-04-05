#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

size_t _hash_func(char *key, size_t size) {
    size_t hash = 0;

    while (*key)
        hash += 37 * hash + (*key++);

    return hash % size;
}

size_t _probe_hash_func(size_t current_key, size_t size) {
    return (LINEAR_PROBE_STRIDE + current_key) % size;
}

int _is_prime(size_t n) {
    size_t i, q;

    for (i = 3; ; i += 2) {
        q = n / i;

        if (q < i)
            return 1;

        if (n == q * i)
            return 0;
    }

    return 1;
}

size_t _next_prime(size_t n) {
    if (n <= 2)
        return 2;

    if (!(n & 1))
        ++n;

    for ( ; 0 == _is_prime(n); n += 2);

    return n;
}

bucket *_bucket_create(char *key, char *value) {
    bucket *b = malloc(sizeof(bucket));

    b->key = strdup(key);
    b->value = strdup(value);

    return b;
}

htable *htable_create() {
    htable *ht = malloc(sizeof(htable));

    ht->capacity = MIN_HASH_SIZE;
    ht->size = 0;
    ht->buckets = calloc(ht->capacity, sizeof(bucket *));

    return ht;
}

void htable_destroy(htable *ht) {
    htable_clear(ht);
    free(ht->buckets);
    free(ht);
}

int htable_is_empty(htable *ht) {
    return 0 == ht->size;
}

size_t htable_size(htable *ht) {
    return ht->size;
}

size_t htable_capacity(htable *ht) {
    return ht->capacity;
}

bucket **htable_find(htable *ht, char *key) {
    size_t hash_key = _hash_func(key, ht->capacity);

    while (NULL != ht->buckets[hash_key]) {
        if (0 == strcmp(ht->buckets[hash_key]->key, key)) {
            return &ht->buckets[hash_key];
        }

        hash_key = _probe_hash_func(hash_key, ht->capacity);
    }

    return NULL;
}

char *htable_get(htable *ht, char *key) {
    bucket **b = htable_find(ht, key);

    if (NULL != b)
        return (*b)->value;

    return NULL;
}

size_t htable_count(htable *ht, char *key) {
    /* the name of this method might be misleading, however
     * if keys where not unique it would make more sense.
     * Since that is the case it can only return 
     * true or false as 0 or 1 */
    return NULL != htable_get(ht, key);
}

bucket *htable_insert(htable *ht, char *key, char *value) {
    size_t hash_key;

    if (htable_load_factor(ht) > MAX_LOAD_FACTOR)
        htable_rehash(ht);

    hash_key = _hash_func(key, ht->capacity);

    while (NULL != ht->buckets[hash_key]) {
        /* overwrite this key */
        if (0 == strcmp(ht->buckets[hash_key]->key, key)) {
            ht->buckets[hash_key]->value = strdup(value);
            return ht->buckets[hash_key];
        }

        /* leverage linear probing */
        hash_key = _probe_hash_func(hash_key, ht->capacity);
        if (NULL == ht->buckets[hash_key]) break;
    }

    ht->buckets[hash_key] = _bucket_create(key, value);
    ++ht->size;

    return ht->buckets[hash_key];
}

void htable_erase(htable *ht, char *key) {
    bucket **b = htable_find(ht, key);

    if (NULL != b) {
        free((*b)->key);
        free((*b)->value);
        free(*b);
        *b = NULL;
        --ht->size;
    }
}

void htable_clear(htable *ht) {
    size_t i;

    for (i = 0; i < ht->capacity; ++i) {
        if (NULL != ht->buckets[i]) {
            free(ht->buckets[i]->value);
            free(ht->buckets[i]->key);
            free(ht->buckets[i]);
            ht->buckets[i] = NULL;
        }
    }

    ht->buckets = realloc(ht->buckets, sizeof(char *)*MIN_HASH_SIZE);
    ht->capacity = MIN_HASH_SIZE;
    ht->size = 0;
}

float htable_load_factor(htable *ht) {
    return ht->size / (float) ht->capacity;
}

void htable_rehash(htable *ht) {
    size_t old_size, i;
    bucket **old_buckets;

    old_size = ht->capacity;
    old_buckets = ht->buckets;

    ht->size = 0;
    ht->capacity = _next_prime(ht->capacity * 2);
    ht->buckets = calloc(ht->capacity, sizeof(bucket *));

    for (i = 0; i < old_size; ++i) {
        if (NULL != old_buckets[i]) {
            htable_insert(ht, old_buckets[i]->key, old_buckets[i]->value);
            free(old_buckets[i]->value);
            free(old_buckets[i]->key);
            free(old_buckets[i]);
        }
    }

    free(old_buckets);
}
