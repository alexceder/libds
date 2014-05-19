#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define run(fn_name)\
    printf(".. %s\n", #fn_name);\
    fn_name()

#include "vector.h"

void test_vector_order() {
    vector *v = vector_create();
    char *dump;
    size_t i;

    vector_push(v, "a");
    vector_push(v, "b");
    vector_pop(v);
    vector_push(v, "c");
    vector_push(v, "d");
    vector_push(v, "e");
    vector_pop(v);
    vector_push(v, "f");

    dump = vector_dump(v);
    assert(0 == strcmp(dump, "{ a c d f }") &&
        "Vector entries should be in correct order.");
    free(dump);

    vector_clear(v);

    dump = vector_dump(v);
    assert(0 == strcmp(dump, "{ }") &&
        "There should not be any entries in the vector after a clear.");
    free(dump);

    for (i = 0; i < 15; ++i) {
        char buf[2] = {'a', '\0'};
        buf[0] = buf[0] + i;
        vector_push(v, buf);
    }

    dump = vector_dump(v);
    assert(0 == strcmp(dump, "{ a b c d e f g h i j k l m n o }") &&
        "Entries should be good too push after a clear");
    free(dump);

    vector_clear(v);

    vector_push(v, "a");
    vector_push(v, "b");
    vector_push(v, "c");

    vector_erase(v, 1);

    dump = vector_dump(v);
    assert(0 == strcmp(dump, "{ a c }") &&
        "Entries should be able to handle removes.");
    free(dump);

    vector_destroy(v);
}

void test_vector_set_get() {
    vector *v = vector_create();

    vector_push(v, "a");

    assert(NULL != vector_get(v, 0) &&
        "Vector value at index 0 should be filled.");
    assert(0 == strcmp(vector_get(v, 0), "a") &&
        "Vector value at index 0 should be equal to a.");
    assert(NULL == vector_get(v, 8) &&
        "Vector value at index 8 should not be filled.");

    vector_set(v, 0, "b");

    assert(0 == strcmp(vector_get(v, 0), "b") &&
        "Vector value at index 0 should be equal to b after a set.");

    assert(0 == strcmp(vector_get_front(v), "b") &&
        "Front value should be b");

    vector_push(v, "c");

    assert(0 == strcmp(vector_get_back(v), "c") &&
        "Back value should be c");

    vector_destroy(v);
}

void test_vector_swap() {
    vector *v = vector_create();

    vector_push(v, "a");
    vector_push(v, "b");
    vector_push(v, "c");

    vector_swap(v, 0, 2);

    assert(0 == strcmp(vector_get(v, 0), "c") &&
        "Value with index 0 should be c after swap");
    assert(0 == strcmp(vector_get(v, 2), "a") &&
        "Value with index 2 should be a after swap");

    vector_destroy(v);
}

void test_vector_resize() {
    vector *v = vector_create();

    assert(1 == vector_capacity(v) &&
        "Vector should have a singluar capacity upon creation.");

    vector_push(v, "a");

    assert(1 == vector_capacity(v) &&
        "Vector should not increase capacity on adding so"
        "that size equals capacity.");

    vector_push(v, "b");

    assert(2 == vector_capacity(v) &&
        "Vector should not increase capacity on adding so"
        "that size equals capacity.");

    vector_push(v, "c");

    assert(4 == vector_capacity(v) &&
        "Vector should not increase capacity on adding so"
        "that size equals capacity.");

    vector_resize(v, 1);

    vector_resize(v, 10);

    assert(1 == vector_size(v) &&
        "Size should be 1 after resize");
    assert(10 == vector_capacity(v) &&
        "Capacity should be 10 after resize");

    vector_push(v, "x"); vector_push(v, "x"); vector_push(v, "x");

    vector_shrink_to_fit(v);

    assert(4 == vector_capacity(v) &&
        "Capacity should be 4 after shrink to fit.");

    vector_destroy(v);
}

void test_vector_insert() {
    vector *v = vector_create();
    char *dump;

    vector_push(v, "a"); vector_push(v, "a"); vector_push(v, "a");

    vector_insert(v, 1, "b");
    vector_insert(v, 9, "should not be inserted");

    dump = vector_dump(v);
    assert(0 == strcmp(dump, "{ a b a a }") &&
        "Insert should work.");
    free(dump);

    vector_destroy(v);
}

void test_vector_erase() {
    vector *v = vector_create();
    char *dump;

    vector_push(v, "a"); vector_push(v, "b"); vector_push(v, "c");

    vector_erase(v, 1);

    dump = vector_dump(v);
    assert(0 == strcmp(dump, "{ a c }") &&
        "Insert should work.");
    free(dump);

    vector_destroy(v);
}

int main(void) {
    printf("\nRunning tests..\n");

    run(test_vector_order);
    run(test_vector_set_get);
    run(test_vector_swap);
    run(test_vector_resize);
    run(test_vector_erase);

    printf("OK\n");
    return 0;
}
