// node.c > implementation of node constructor / node destructor

#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  INFO: node constructor

struct node node_constructor(void *data, int size) {
	if (size < 1) {
		printf("=== invalid size ===\n");
		exit(1);
	}
	struct node node;

	node.data = malloc(size); // allocate the size of data
	memcpy(node.data, data, size);

	node.next = NULL;
	node.previous = NULL;
	return node;
}

//  INFO: node destructor

void node_destructor(struct node *node) {
	free(node->data);
	free(node);
} /* NODE_C */
