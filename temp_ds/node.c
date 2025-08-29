#include "node.h"

struct node node_constructor(void *data, int size) {
	if (size < 1) {
		printf("=== invalid size ===\n");
		exit(1);
	}
	struct node node;

	node.data = malloc(size);
	memcpy(node.data, data, size);

	node.next = NULL;

	return node;
}

void node_destructor(struct node *node) {
	free(node->data);
	free(node);
} /* NODE_C */
