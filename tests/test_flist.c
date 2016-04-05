#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define run(fn_name)\
    printf(".. %s\n", #fn_name);\
    fn_name()

#include "flist.h"

void test_flist_size() {
    flist *l= flist_create();

    assert(0 == flist_size(l) &&
        "Counter should be zero after instatiation.");

    flist_insert(l, "a");
    flist_insert(l, "b");

    assert(2 == flist_size(l) &&
        "Counter should be equal to 2 after inserting twice.");

    flist_clear(l);

    assert(0 == flist_size(l) &&
        "Counter should be 0 after emptying a flist.");

    flist_destroy(l);
}

void test_flist_value_exists() {
    flist *l = flist_create();

    flist_insert(l, "foo");

    assert(1 == flist_value_exists(l, "foo") &&
        "Value foo should exists in the flist.");

    assert(0 == flist_value_exists(l, "bar") &&
        "Value bar should not exists in the flist.");

    flist_destroy(l);
}

void test_flist_order() {
    flist *l = flist_create();
    char *dump;

    flist_insert(l, "c"); flist_insert(l, "a");
    flist_insert(l, "f"); flist_insert(l, "b");
    flist_insert(l, "e"); flist_insert(l, "d");

    dump = flist_dump(l);

    assert(0 == strcmp(dump, "{ a b c d e f }") &&
        "List entries should be in correct order.");

    free(dump);
    flist_destroy(l);
}

int main(void) {
    printf("\nRunning tests..\n");

    run(test_flist_size);
    run(test_flist_value_exists);
    run(test_flist_order);

    printf("OK\n");
    return 0;
}
