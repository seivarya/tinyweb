#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "../node/node.h"

struct binary_tree {

	struct node *head;

	int (*compare)(void *data_fir, void *data_sec);
	void (*insert)(struct binary_tree *binary_tree, void *data);

	void * (*search)(struct binary_tree *binary_tree, void *data);
};

struct binary_tree binary_tree_constructor(void);

#endif /* BINARY_TREE */
