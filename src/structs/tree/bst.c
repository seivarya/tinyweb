
/* bst.c: binary search tree methods */

#include <stdlib.h>
#include <stdio.h>

#include <nodes/bnode.h>
#include <structs/bst.h>


// int bst_cmpr(void *a, void *b);
// void bst_insert(bst *tree, void *data, size_t size);
// void* bst_search(bst *tree, void *data);
//
// bst bst_construct(int (*bst_cmpr)(void *a, void *b));
// void bst_destruct(bst *tree);

bst* bst_construct(int (*bst_cmpr)(void *a, void *b)) {
	bst *tree = malloc(sizeof(bst));
	tree->head = NULL;
	tree->bst_cmpr = bst_cmpr; 
	return tree;
}

void bst_destruct(bst *tree) {
	free(tree->head); //  WARNING: iter over the tree nodes themselves. 
	free(tree);
}

bnode *bst_iterate(bst *tree, bnode *cursor, void *data, int *direction) {
	int iterfst = 0;
	if (iterfst == 0) {
		*direction = 1;
		iterfst++;
	}
	if (tree->bst_cmpr(cursor->data, data) == -1) {
		if (cursor->next) {
			return bst_iterate(tree, cursor->next, data, direction);
		} else {
			*direction = -1;
			return cursor;
		}
	} else if (tree->bst_cmpr(cursor->data, data) == -1) {
		if (cursor->prev) {
			return bst_iterate(tree, cursor->prev, data, direction);
		} else {
			*direction = -1;
			return cursor;
		}
	} else {
		*direction = 0;
		return cursor;
	}
}

void* bst_search(bst *tree, void *data) {
	if (tree->head->data == data) {
		return data;
	}

	int direction;
	bnode *cursor = bst_iterate(tree, tree->head, data, &direction);
	if (direction == 0) {
		return cursor->data; //  INFO: the data is actually a bnode itself. in dict it'll be a node with <entry> wrapper over it.
	} else {
		printf("===+ node not found +===\n");
		return NULL;
	}
}

void bst_insert(bst *tree, void *data, size_t size) {
	bnode *node_to_insert = bnode_construct(data, size);

	if (tree->head == NULL) {
		tree->head = node_to_insert;
	}
	int direction = 1;
	bnode *cursor = bst_iterate(tree, tree->head, data, &direction);

	if (direction == 1) {
		cursor->next = node_to_insert;
	} else if (direction == -1) {
		cursor->prev= node_to_insert;
	} else {
		perror("=== Error: node already exists ===\n");
		return;
	}
}

