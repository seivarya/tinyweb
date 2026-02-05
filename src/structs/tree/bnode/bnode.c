#include <stdio.h>
#include <string.h>

#include "bnode.h"

bnode* bnode_construct(void *data, size_t size) {
	bnode *node = malloc(sizeof(bnode));
	if (!node) {
		perror("=== malloc failed: bnode_construct(): sizeof(bnode) ===");
		return NULL;
	}

	node->data = malloc(size);
	if (!node->data) {
		perror("=== malloc failed: bnode_construct(): node->data ===");
		free(node);
		return NULL;
	}
	memcpy(node->data, data, size);
	node->next = NULL;
	node->prev = NULL;

	return node;
}

void bnode_destruct(bnode* node) {
	if (!node)
		return;
	if (node->data) {
		free(node->data);
		node->data = NULL;
	}
	
	free(node);
} /* bnode_c */
