#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bst.h"

bstnode *_bstnode_create(char *value, bstnode* left, bstnode* right) {
    bstnode *n = malloc(sizeof(bstnode));

    n->value = strdup(value);
    n->lthread = n->rthread = 1;
    n->left = left;
    n->right = right;

    return n;
}

size_t _bstnode_insert(bstnode *n, char *value) {
    if (strcmp(n->value, value) < 0) {
        if (!n->lthread) {
            return _bstnode_insert(n->left, value);
        } else {
            bstnode *temp = n->left;
            n->left = _bstnode_create(value, temp, n);
            n->lthread = 0;
            return 1;
        }
    }
    
    else if (strcmp(n->value, value) > 0) {
        if (!n->rthread) {
            return _bstnode_insert(n->right, value);
        } else {
            bstnode *temp = n->right;
            n->right = _bstnode_create(value, n, temp);
            n->rthread = 0;
            return 1;
        }
    }

    return 0;
}

size_t bst_count(bst *b) {
    return b->counter;
}

bstnode *_bstnode_find(bstnode *n, char *value) {
    if (strcmp(n->value, value) < 0) {
        if (!n->lthread)
            return _bstnode_find(n->left, value);

    } else if (strcmp(n->value, value) > 0) {
        if (!n->rthread)
            return _bstnode_find(n->right, value);

    } else {
        return n;
    }

    return NULL;
}

bstnode *_bstnode_find_min(bstnode *n) {
    if (!n->lthread)
        return _bstnode_find_min(n->left);

    return n;
}

bstnode *_bstnode_find_max(bstnode *n) {
    if (!n->rthread)
        return _bstnode_find_max(n->right);

    return n;
}

size_t _bstnode_remove(bstnode *n, char *value, bstnode *parent, size_t is_right) {
    /* two first are just traversals */
    if (strcmp(n->value, value) < 0) {
        if (!n->lthread)
            return _bstnode_remove(n->left, value, n, 0);
    }

    else if (strcmp(n->value, value) > 0) {
        if (!n->rthread)
            return _bstnode_remove(n->right, value, n, 1);
    }

    else {
        if (!n->lthread && !n->rthread) {
            bstnode *min = _bstnode_find_min(n->right);
            n->value = min->value;
            return _bstnode_remove(n->right, n->value, n, 1);
        }

        else {
            _bstnode_remove_bstnode(n, parent, is_right);
            return 1;
        }
    }

    return 0;
}

void _bstnode_remove_bstnode(bstnode *n, bstnode *parent, size_t is_right) {
    if (!is_right) {
        if (n->lthread && !n->rthread) {
            bstnode *right_min = _bstnode_find_min(n->right);
            parent->left = n->right;
            right_min->left = n->left;
        }

        else if (!n->lthread && n->rthread) {
            bstnode *left_max= _bstnode_find_max(n->left);
            parent->left = n->left;
            left_max->right = parent;
        }

        else if (n->lthread && n->rthread) {
            parent->left = n->left;
            parent->lthread = 1;
        }
    }

    else {
        if (n->lthread && !n->rthread) {
            bstnode *right_min = _bstnode_find_min(n->right);
            parent->right = n->right;
            right_min->left = n->right;
        }

        else if (!n->lthread && n->rthread) {
            bstnode *left_max= _bstnode_find_max(n->left);
            parent->right = n->left;
            left_max->right = n->right;
        }

        else if (n->lthread && n->rthread) {
            parent->right = n->right;
            parent->rthread = 1;
        }
    }

    free(n->value);
    free(n);
}

bst *bst_create() {
    bst *tree = malloc(sizeof(bst));

    tree->root = _bstnode_create("", NULL, NULL);
    tree->root->left = tree->root;
    tree->root->right = tree->root;
    tree->counter = 0;

    return tree;
}

void bst_insert(bst *b, char *value) {
    if (0 == b->counter) {
        b->root->left = _bstnode_create(value, b->root, b->root);
        b->counter = 1;
    } else {
        b->counter += _bstnode_insert(b->root->left, value);
    }
}

bstnode *bst_find(bst *b, char *value) {
    if (0 != b->counter) {
        return _bstnode_find(b->root->left, value);
    }

    return NULL;
}

size_t bst_value_exists(bst *b, char *value) {
    return bst_find(b, value) != NULL ? 1 : 0;
}

size_t bst_remove(bst *b, char *value) {
    size_t removed = _bstnode_remove(b->root->left, value, b->root, 0);
    b->counter -= removed;
    return removed;
}

/*void _bstnode_inorder_empty(bstnode *n) {*/
    /* I DON'T EVEN */
/*}*/

bstnode *_bstnode_next(bstnode *n) {
    if (n->rthread) {
        return n->right;
    }

    return _bstnode_find_min(n->right);
}

void bst_empty(bst *b) {
    if (0 != b->counter) {
        /*_bstnode_inorder_empty(b->root->left);*/
    }
}

void bst_destroy(bst *b) {
    bst_empty(b);

    free(b->root->value);
    free(b->root);
    free(b);
}
