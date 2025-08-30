#include "binary_tree.h"

struct node * create_node(void *data, int size);
void destroy_node(struct node *node_to_destroy);

void * search(struct binary_tree *tree, void *data);
void insert(struct binary_tree *tree, void *data, int size);

struct binary_tree binary_tree_constructor(int (*compare)(void *data_fir, void *data_sec)) {
	struct binary_tree tree;

	tree.compare = compare;
	tree.insert = insert;
	tree.search = search;

	return tree;
}


struct node * create_node(void *data, int size) {
	struct node *new_node = (struct node *)malloc(sizeof(struct node *));
	*new_node = node_constructor(data, size);
	return new_node;
}

void destroy_node(struct node *node_to_destroy) {
	node_destructor(node_to_destroy);
}

struct node * iterate(struct binary_tree *tree, struct node *cursor, void *data, int *direction) {
	if (tree->compare(cursor->data, data) == 1) {
		if (cursor->next) {
			return iterate(tree, cursor->next, data, direction);
		} else {
			*direction = 1;
			return cursor;
		} 
	} else if (tree->compare(cursor->data, data) == -1) {
		if (cursor->previous) {
			return iterate(tree, cursor->previous, data, direction);
		} else {
			*direction = -1;
			return cursor;
		}
	} else {
		*direction = 0;
		return cursor;
	}
}

void * search(struct binary_tree *tree, void *data) {
	int direction;
	struct node *cursor = iterate(tree, tree->head, data, &direction);

	if (direction == 0) {
		return cursor->data;
	} else {
		return NULL;
	}
}

void insert(struct binary_tree *tree, void *data, int size) {
	int direction;
	struct node *cursor = iterate(tree, tree->head, data, &direction);
	
	if (direction == 1) {
		cursor->next = create_node(data, size);
	} else if (direction == -1) {
		cursor->previous = create_node(data, size);
	} else {
		printf("node already exists\n");
		exit(1);
	}
}
