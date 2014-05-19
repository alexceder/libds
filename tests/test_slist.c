#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define run(fn_name)\
    printf(".. %s\n", #fn_name);\
    fn_name()

#include "slist.h"

void test_list_size() {
    list *l= list_create();

    assert(0 == list_size(l) &&
        "Counter should be zero after instatiation.");

    list_insert(l, "a");
    list_insert(l, "b");

    assert(2 == list_size(l) &&
        "Counter should be equal to 2 after inserting twice.");

    list_clear(l);

    assert(0 == list_size(l) &&
        "Counter should be 0 after emptying a list.");

    list_destroy(l);
}

void test_list_value_exists() {
    list *l = list_create();

    list_insert(l, "foo");

    assert(1 == list_value_exists(l, "foo") &&
        "Value foo should exists in the list.");

    assert(0 == list_value_exists(l, "bar") &&
        "Value bar should not exists in the list.");

    list_destroy(l);
}

void test_list_order() {
    list *l = list_create();
    char *dump;

    list_insert(l, "c"); list_insert(l, "a");
    list_insert(l, "f"); list_insert(l, "b");
    list_insert(l, "e"); list_insert(l, "d");

    dump = list_dump(l);

    assert(0 == strcmp(dump, "{ a b c d e f }") &&
        "List entries should be in correct order.");

    free(dump);
    list_destroy(l);
}

int main(void) {
    printf("\nRunning tests..\n");

    run(test_list_size);
    run(test_list_value_exists);
    run(test_list_order);

    printf("OK\n");
    return 0;
}
