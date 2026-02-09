
/* bst.c: binary search tree methods */

#include <stdlib.h>
#include <stdio.h>

#include <nodes/bnode.h>
#include <structs/bst.h>

/* info: private methods (rvlib-style validation) */

static inline int _validate_bst_ptr(bst *tree) {
	if (tree == NULL) {
		fprintf(stderr, "Error: %s: BST pointer is NULL.\n", __func__);
		return 0;
	}
	if (tree->bst_cmpr == NULL) {
		fprintf(stderr, "Error: %s: BST compare function is NULL.\n", __func__);
		return 0;
	}
	return 1;
}

static inline void _validate_bnode_construction(bst *tree, bnode *node) {
	if (!node) {
		fprintf(stderr, "Error: %s: Failed to construct BST node, aborting.\n", __func__);
		/* tree may be partially built at this point; caller must decide how to recover */
		exit(3);
	}
}

static inline int _validate_bst_nonempty(bst *tree) {
	if (!_validate_bst_ptr(tree))
		return 0;
	if (tree->head == NULL) {
		fprintf(stderr, "Error: %s: BST is empty.\n", __func__);
		return 0;
	}
	return 1;
}

/* info: public methods */

bst* bst_construct(int (*bst_cmpr)(void *a, void *b)) {
	bst *tree = malloc(sizeof(bst));
	if (!tree) {
		fprintf(stderr, "=== error: bst_construct(): malloc failed ===\n");
		return NULL;
	}
	tree->head = NULL;
	tree->bst_cmpr = bst_cmpr;
	return tree;
}

void bst_destruct(bst *tree) {
	if (!_validate_bst_ptr(tree))
		return;

	/* WARNING: this only frees the head node; a full tree traversal
	 * should be implemented to avoid leaks if the tree owns its nodes. */
	free(tree->head);
	free(tree);
}

bnode *bst_iterate(bst *tree, bnode *cursor, void *data, int *direction) {
	if (!_validate_bst_ptr(tree) || cursor == NULL || data == NULL || direction == NULL)
		return NULL;

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
	if (!_validate_bst_nonempty(tree) || data == NULL)
		return NULL;

	if (tree->head->data == data) {
		return data;
	}

	int direction = 0;
	bnode *cursor = bst_iterate(tree, tree->head, data, &direction);
	if (!cursor)
		return NULL;

	if (direction == 0) {
		/* INFO: the data is actually a bnode itself. in dict it'll be a node with <entry> wrapper over it. */
		return cursor->data;
	} else {
		fprintf(stderr, "Error: %s: node not found in BST.\n", __func__);
		return NULL;
	}
}

void bst_insert(bst *tree, void *data, size_t size) {
	if (!_validate_bst_ptr(tree) || data == NULL)
		return;

	bnode *node_to_insert = bnode_construct(data, size);
	_validate_bnode_construction(tree, node_to_insert);

	if (tree->head == NULL) {
		tree->head = node_to_insert;
		return;
	}

	int direction = 1;
	bnode *cursor = bst_iterate(tree, tree->head, data, &direction);
	if (!cursor)
		return;

	if (direction == 1) {
		cursor->next = node_to_insert;
	} else if (direction == -1) {
		cursor->prev = node_to_insert;
	} else {
		fprintf(stderr, "Error: %s: node already exists in BST.\n", __func__);
		return;
	}
}

