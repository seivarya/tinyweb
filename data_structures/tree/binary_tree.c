#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

//  INFO: function prototypes

struct node * create_node_tree(void *data, int size);

void destroy_node(struct node *node_to_destroy);
void * search(struct binary_tree *tree, void *data);
void insert(struct binary_tree *tree, void *data, int size);

//  INFO: binary tree constructor

struct binary_tree binary_tree_constructor(int (*compare)(void *data_fir, void *data_sec)) {
	struct binary_tree tree;

	tree.binary_node_compare= compare;
	tree.binary_node_insert= insert;
	tree.binary_node_search= search;
	tree.head = NULL;

	return tree;
}

//  INFO: bianry tree destructor

void binary_tree_destructor(struct binary_tree *tree) {
	free(tree->head);
	free(tree);
}

//  INFO: private methods

struct node * create_node_tree(void *data, int size) {
	struct node *new_node = malloc(sizeof(struct node));
	if (!new_node) {
		perror("=== malloc failed ===");
		exit(1);
	}
	*new_node = node_constructor(data, size); 
	return new_node;

}

struct node * iterate_tree(struct binary_tree *tree, struct node *cursor, void *data, int *direction) {

	int test = 0;
	printf("data in tree: %s\n", (char *)data);
	if (test == 0) {
		*direction = 1; 
		test++;
	}
	if (tree->binary_node_compare(cursor->data, data) == 1) {
		if (cursor->next) {
			return iterate_tree(tree, cursor->next, data, direction);
		} else {
			*direction = 1;
			return cursor;
		} 
	} else if (tree->binary_node_compare(cursor->data, data) == -1) {
		if (cursor->previous) {
			return iterate_tree(tree, cursor->previous, data, direction);
		} else {
			*direction = -1;
			return cursor;
		}
	} else {
		*direction = 0;
		return cursor;
	}
}

//  INFO: public methods

void * search(struct binary_tree *tree, void *data) {
	int direction;
	struct node *cursor = iterate_tree(tree, tree->head, data, &direction);

	if (direction == 0) {
		return cursor->data;
	} else {
		return NULL;
	}
}

void insert(struct binary_tree *tree, void *data, int size) {

	int direction;
	if (tree->head == NULL) {
		tree->head = create_node_tree(data, size);
		return; // case for head.
	}

	struct node *cursor = iterate_tree(tree, tree->head, data, &direction);

	if (direction == 1) {
		cursor->next = create_node_tree(data, size);
	} else if (direction == -1) {
		cursor->previous = create_node_tree(data, size);
	} else {
		printf("node already exists\n");
		exit(9);
	}
}
