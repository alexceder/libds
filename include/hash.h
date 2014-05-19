#include <stddef.h>

#ifndef HASH_H
#define HASH_H

#define MIN_HASH_SIZE 13
#define MAX_LOAD_FACTOR .5f
#define LINEAR_PROBE_STRIDE 1

size_t _hash_func(char *key, size_t size);
size_t _probe_hash_func(size_t current_key, size_t size);

int _is_prime(size_t n);
size_t _next_prime(size_t n);

struct bucket {
    char *key;
    char *value;
};

typedef struct bucket bucket;

bucket *_bucket_create(char *key, char *value);

struct htable {
    bucket **buckets;
    size_t capacity;
    size_t size;
};

typedef struct htable htable;

/* constructor & destructor */
htable *htable_create();
void htable_destroy(htable *ht);

/* capacity */
int htable_is_empty(htable *ht);
size_t htable_size(htable *ht);
size_t htable_capacity(htable *ht);

/* accessors */
bucket *htable_find(htable *ht, char *key);
char *htable_get(htable *ht, char *key);
size_t htable_count(htable *ht, char *key);

/* modifiers */
bucket *htable_insert(htable *ht, char *key, char *value);
void htable_clear(htable *ht);
void htable_erase(htable *ht, char *key);

/* hash policy */
float htable_load_factor(htable *ht);
void htable_rehash(htable *ht);
/*void htable_reserve(htable *ht, size_t n)*/
/*int htable_key_eq(htable *ht, char *first, char *second);*/

#endif /* HASH_H */
