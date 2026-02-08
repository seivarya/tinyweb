/* bst.h: binary search tree header file */

#ifndef BST_H
#define BST_H

#include "nodes/bnode.h"

typedef struct bst {
	bnode *head;
	int (*bst_cmpr)(void *a, void *b);
} bst;

int bst_cmpr(void *a, void *b);
void bst_insert(bst *tree, void *data, size_t size);
void* bst_search(bst *tree, void *data);
bnode *bst_iterate(bst *tree, bnode *cursor, void *data, int *direction);

bst* bst_construct(int (*bst_cmpr)(void *a, void *b));
void bst_destruct(bst *tree);

#endif
