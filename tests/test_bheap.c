#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define run(fn_name)\
    printf(".. %s\n", #fn_name);\
    fn_name()

#include "bheap.h"

#define dump_heap()\
    dump = heap_dump(h);\
    printf("%s\n", dump);\
    free(dump)

void test_heap_create_from_array() {
    char *dump;
    char *letters[] = {"a", "b", "c", "d", "e"};
    char *letters_unordered[] = {"c", "a", "e", "b", "d"};

    /* suite one */
    heap *h = heap_create_from_array(letters, 5);

    dump = vector_dump(h->values);
    assert(0 == strcmp(dump, "{ (dummy) a b c d e }") &&
        "Ordering should be correct after a few inserts and pops.");
    free(dump);

    heap_destroy(h);

    /* suite two */
    h = heap_create_from_array(letters_unordered, 5);

    dump = vector_dump(h->values);
    assert(0 == strcmp(dump, "{ (dummy) a b e c d }") &&
        "Ordering should be correct after a few inserts and pops.");
    free(dump);

    heap_destroy(h);
}

void test_heap_insert_pop() {
    char *dump;
    heap *h = heap_create();

    heap_insert(h, "b");
    heap_insert(h, "d");
    heap_pop(h);
    heap_insert(h, "a");
    heap_pop(h);
    heap_insert(h, "c");
    heap_insert(h, "g");
    heap_pop(h);
    heap_insert(h, "f");
    heap_insert(h, "e");
    heap_pop(h);

    dump = vector_dump(h->values);
    assert(0 == strcmp(dump, "{ (dummy) e g f }") &&
        "Ordering should be correct after a few inserts and pops.");
    free(dump);

    heap_destroy(h);
}

int main(void) {
    printf("\nRunning tests..\n");

    run(test_heap_insert_pop);
    run(test_heap_create_from_array);

    printf("OK\n");
    return 0;
}
