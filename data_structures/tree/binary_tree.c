#include "binary_tree.h"

struct node * create_node(void *data, int size);
void destroy_node(struct node *node_to_destroy);

struct binary_tree binary_tree_constructor(int (*compare)(void *data_fir, void *data_sec)) {
	struct binary_tree tree;

	tree.compare = compare;
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

//FIX: i think it's incorrect maybe

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
		direction = 0;
		return cursor;
	}
}

