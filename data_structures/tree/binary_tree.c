#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

//  INFO: binary tree constructor

struct binary_tree binary_tree_constructor(int (*compare)(void *data_fir, void *data_sec)) {
	struct binary_tree tree;

	tree.binary_node_compare = compare;
	tree.binary_node_insert = insert_tree_node;
	tree.binary_node_search = search_tree_node;
	tree.head = NULL;

	return tree;
}

//  INFO: bianry tree destructor

void binary_tree_destructor(struct binary_tree *tree) {
	free(tree->head);
	free(tree);
}

//  INFO: public methods

void *search_tree_node(struct binary_tree *tree, void *data) {
	if (tree->head->data == data) {
		return data;
	}

	int direction;
	struct node *cursor = iterate_tree_node(tree, tree->head, data, &direction);

	if (direction == 0) {
		return cursor->data; //  INFO: the data in cursor is actually a node.. in dict_ it'll be a node that's wrapped around struct entry 
	} else {
		return NULL; // data not found 
	}
}

void insert_tree_node(struct binary_tree *tree, void *data, int size) {
	if (tree->head == NULL) {
		tree->head = create_tree_node(data, size); //  INFO: inserting data at head in case of NULL head
		return;
	}

	int direction = 1;
	struct node *cursor = iterate_tree_node(tree, tree->head, data, &direction);

	if (direction == 1) {
		cursor->next = create_tree_node(data, size);
	} else if (direction == -1) {
		cursor->previous = create_tree_node(data, size);
	} else {
		printf("=== node already exists ===\n");
		return;
	}
}

//  INFO: private methods

struct node *create_tree_node(void *data, int size) {
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	*new_node = node_constructor(data, size);

	return new_node;
}

struct node *iterate_tree_node(struct binary_tree *tree, struct node *cursor, void *data, int *direction) {
	int iter_first = 0;

	if (iter_first == 0) {
		*direction = 1;
		iter_first++;
	}

	if (tree->binary_node_compare(cursor->data, data) == 1) {
		if (cursor->next) { //  INFO: to check weather the node below the existing node is NULL or not
			return iterate_tree_node(tree, cursor->next, data, direction);
		} else {
			*direction = 1;
			return cursor;
		}
	} else if (tree->binary_node_compare(cursor->data, data) == -1) {
		if (cursor->previous) {
			return iterate_tree_node(tree, cursor->previous, data, direction);
		} else {
			*direction = -1;
			return cursor;
		}
	} else {
		*direction = 0;
		return cursor;
	}
} /* BINARY_TREE */
