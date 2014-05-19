#include <stddef.h>

#ifndef BST_H
#define BST_H

struct bstnode;

typedef struct bstnode bstnode;

struct bstnode {
    char *value;
    bstnode *left;
    bstnode *right;
    unsigned short lthread;
    unsigned short rthread;
};

bstnode *_bstnode_create(char *value, bstnode* left, bstnode* right);
size_t _bstnode_insert(bstnode *n, char *value);
size_t _bstnode_remove(bstnode *n, char *value, bstnode *parent, size_t is_right);
void _bstnode_remove_bstnode(bstnode *n, bstnode *parent, size_t is_right);
bstnode *_bstnode_find_min(bstnode *n);
bstnode *_bstnode_find_max(bstnode *n);

struct bst {
    bstnode *root;
    size_t counter;
};

typedef struct bst bst;

bst *bst_create();
void bst_insert(bst *b, char *value);
bstnode *bst_find(bst *b, char *value);
size_t bst_value_exists(bst *b, char *value);
size_t bst_count(bst *b);
size_t bst_remove(bst *b, char *value);
void bst_empty(bst *b);
void bst_destroy(bst *b);

#endif /* BST_H */
