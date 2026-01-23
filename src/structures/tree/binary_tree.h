#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "../node/node.h"

//  INFO: binary tree object initialization

struct binary_tree {

	struct node *head;

	int (*binary_node_compare)(void *data_fir, void *data_sec);
	void (*binary_node_insert)(struct binary_tree *tree, void *data, int size);
	void * (*binary_node_search)(struct binary_tree *tree, void *data);
};

//  INFO: method
struct binary_tree binary_tree_constructor(int (*compare)(void *data_fir, void *data_sec));
void binary_tree_destructor(struct binary_tree *tree);

//  INFO: function prototypes

struct node *create_tree_node(void *data, int size);
struct node *iterate_tree_node(struct binary_tree *tree, struct node *cursor, void *data, int *direction);

void destroy_tree_node(struct node *node_to_destroy);
void *search_tree_node(struct binary_tree *tree, void *data);
void insert_tree_node(struct binary_tree *tree, void *data, int size);

#endif /* BINARY_TREE */
