/* bst.h: binary search tree header file */

#include <structs/tree/bst_node.h>

#ifndef BST_H
#define BST_H
typedef struct bst {
        bst_node *head;
        int (*bst_cmpr)(void *a, void *b);
} bst;

int bst_cmpr(void *a, void *b);
void bst_insert(bst *tree, void *data, size_t size);
void *bst_search(bst *tree, void *data);
bst_node *bst_iterate(bst *tree, bst_node *cursor, void *data, int *direction);

bst *bst_construct(int (*bst_cmpr)(void *a, void *b));
void bst_destruct(bst *tree);

#endif
