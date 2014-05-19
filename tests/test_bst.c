#include <stdio.h>
#include <assert.h>

#define run(fn_name)\
    printf(".. %s\n", #fn_name);\
    fn_name()

#include "bst.h"

void test_bst_count() {
    bst *tree = bst_create();

    assert(0 == bst_count(tree) &&
        "Count should be 0 just after initialization.");

    bst_insert(tree, "a");
    bst_insert(tree, "b");
    bst_insert(tree, "c");

    assert(3 == bst_count(tree) &&
        "Count should be 3 after three insertions.");

    bst_destroy(tree);
}

void test_bst_value_exists() {
    bst *tree = bst_create();

    assert(0 == bst_value_exists(tree, "a") &&
        "Value a should not exist right after create.");

    bst_insert(tree, "a");
    bst_insert(tree, "b");
    bst_insert(tree, "c");

    assert(1 == bst_value_exists(tree, "a") &&
        "Value a should exist.");
    assert(1 == bst_value_exists(tree, "b") &&
        "Value b should exist.");
    assert(1 == bst_value_exists(tree, "c") &&
        "Value c should exist.");
    assert(0 == bst_value_exists(tree, "z") &&
        "Value z should not exist.");

    bst_remove(tree, "a");

    assert(0 == bst_value_exists(tree, "a") &&
        "Value a should not exist after deletion.");
    assert(1 == bst_value_exists(tree, "b") &&
        "Value b should exist.");
    assert(1 == bst_value_exists(tree, "c") &&
        "Value c should exist.");

    bst_destroy(tree);
}

int main(void) {
    printf("\nRunning tests..\n");

    run(test_bst_value_exists);
    run(test_bst_count);

    printf("OK\n");
    return 0;
}
