#include "node.h"

#define TYPE_HANDLE(D_TYPE) \
node.data = malloc(sizeof(D_TYPE) * size); \
memcpy(node.data, data, (sizeof(D_TYPE) * size)); \
break;


struct node node_constructor(void *data, int data_type, int size) {
	if (size < 1) {
		printf("=== invalid size ===\n");
		exit(1);
	}
	struct node node;

	switch (data_type) {

	
		case Int: TYPE_HANDLE(int);
		case Float: TYPE_HANDLE(float);
		case Char: TYPE_HANDLE(char);
		case Double: TYPE_HANDLE(double);
		case Long: TYPE_HANDLE(long);
		case Bool: TYPE_HANDLE(bool);
		default: {
			printf("=== invalid data type selected. ===\n");
			exit(1);
		}
	}
	node.size = size;
	node.next = NULL;
	node.data_type = data_type;

	return node;
}

void node_destructor(struct node *node) {
	if (!node) return;
	free(node->data);
	free(node);
}
