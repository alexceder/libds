#include <stdio.h>
#include <assert.h>

#define run(fn_name)\
    printf(".. %s\n", #fn_name);\
    fn_name()

#include <string.h>
#include "hash.h"

void test_htable_get() {
    htable *ht = htable_create();

    htable_insert(ht, "two", "2nd value");

    assert(NULL == htable_get(ht, "one")
        && "First value should be NULL");

    assert(NULL != htable_get(ht, "two")
        && "Second value should not equal NULL");

    assert(0 == strcmp("2nd value", htable_get(ht, "two"))
        && "Second value should be equal to 2nd value");

    htable_destroy(ht);
}

void test_htable_probing() {
    htable *ht = htable_create();
    size_t capacity = htable_capacity(ht);

    assert(_hash_func("one", capacity) == _hash_func("seven", capacity)
        && "Make sure that the keys gives the same key");

    htable_insert(ht, "one", "1st value");
    htable_insert(ht, "seven", "7th value");

    assert(0 == strcmp("1st value", htable_get(ht, "one"))
        && "First value should be equal to 1st value");

    assert(0 == strcmp("7th value", htable_get(ht, "seven"))
        && "Seventh value should be equal to 7th value");

    htable_destroy(ht);
}

void test_htable_rehash() {
    htable *ht = htable_create();

    assert(htable_capacity(ht) == MIN_HASH_SIZE
        && "Size is MIN_HASH_SIZE after creation.");

    htable_insert(ht, "one", "1st value");
    htable_insert(ht, "two", "2nd value");
    htable_insert(ht, "three", "3rd value");
    htable_insert(ht, "four", "4th value");
    htable_insert(ht, "five", "5th value");
    htable_insert(ht, "six", "6th value");
    htable_insert(ht, "seven", "7th value");
    htable_insert(ht, "eight", "8th value");
    htable_insert(ht, "nine", "9th value");
    htable_insert(ht, "ten", "10th value");
    htable_insert(ht, "eleven", "11th value");
    htable_insert(ht, "twelve", "12th value");

    assert(htable_capacity(ht) == 29
        && "Size is 29 after rehash.");

    assert(0 == strcmp("1st value", htable_get(ht, "one"))
        && "First value should be equal to 1st value");

    assert(0 == strcmp("2nd value", htable_get(ht, "two"))
        && "Second value should be equal to 2nd value");

    assert(0 == strcmp("7th value", htable_get(ht, "seven"))
        && "Third value should be equal to 3rd value");

    htable_destroy(ht);
}

void test_htable_size() {
    htable *ht = htable_create();

    assert(0 == htable_size(ht)
        && "Count should be 0 upon creation.");

    htable_insert(ht, "one", "1st value");
    htable_insert(ht, "two", "2nd value");
    htable_insert(ht, "three", "3rd value");

    assert(3 == htable_size(ht)
        && "Count should be 3 after three insertions.");

    htable_clear(ht);

    assert(0 == htable_size(ht)
        && "Count should be 0 after clear.");

    htable_destroy(ht);
}

void test_htable_erase() {
    htable *ht = htable_create();

    htable_insert(ht, "one", "1st value");
    htable_insert(ht, "two", "2nd value");

    htable_erase(ht, "one");

    assert(0 == htable_count(ht, "one")
        && "Bucket with key one should not exist.");

    htable_destroy(ht);
}

int main(void) {
    printf("\nRunning tests..\n");

    run(test_htable_get);
    run(test_htable_probing);
    run(test_htable_rehash);
    run(test_htable_size);
    run(test_htable_erase);

    printf("OK\n");
    return 0;
}
