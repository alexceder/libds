#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define run(fn_name)\
    printf(".. %s\n", #fn_name);\
    fn_name()

#include "list.h"

void test_list_size() {
    list *l= list_create();
    list_iter lit = list_iter_front(l);

    assert(0 == list_size(l) &&
        "Counter should be zero after instatiation.");

    list_insert(l, lit, "a");
    list_insert(l, lit, "b");

    assert(2 == list_size(l) &&
        "Counter should be equal to 2 after inserting twice.");

    list_clear(l);

    assert(0 == list_size(l) &&
        "Counter should be 0 after emptying a list.");

    list_destroy(l);
}

void test_list_order() {
    list *l = list_create();
    list_iter lit = list_iter_front(l);
    char *dump;

    list_insert(l, lit, "c"); list_insert(l, lit, "a");
    list_insert(l, lit, "f"); list_insert(l, lit, "b");
    list_insert(l, lit, "e"); list_insert(l, lit, "d");

    dump = list_dump(l);

    assert(0 == strcmp(dump, "{ a b c d e f }") &&
        "List entries should be in correct order.");

    free(dump);
    list_destroy(l);
}

int main(void) {
    printf("\nRunning tests..\n");

    run(test_list_size);
    run(test_list_order);

    printf("OK\n");
    return 0;
}
