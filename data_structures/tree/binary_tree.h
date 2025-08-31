#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "../node/node.h"

struct binary_tree {

	struct node *head;

	int (*compare)(void *data_fir, void *data_sec);
	void (*insert)(struct binary_tree *tree, void *data, int size);

	void * (*search)(struct binary_tree *tree, void *data);
};

struct binary_tree binary_tree_constructor(int (*compare)(void *data_fir, void *data_sec));
void binary_tree_destructor(struct binary_tree *tree);
#endif /* BINARY_TREE */
