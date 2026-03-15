/* bst_node.h: binary search tree node interface */

#ifndef BST_NODE_H
#define BST_NODE_H

#include <stdlib.h>

typedef struct bst_node bst_node;

struct bst_node {
	void *data;
	bst_node *next;
	bst_node *prev;
};

bst_node *bst_node_construct(void *data, size_t size);
void bst_node_destruct(bst_node *node);

#endif /* bst_node_h */
