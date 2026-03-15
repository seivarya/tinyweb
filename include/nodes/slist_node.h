/* slist_node.h: singly linked list node interface */

#ifndef SLIST_NODE_H
#define SLIST_NODE_H

#include <stdlib.h>

typedef struct td td;

struct td {
	char *name;
};

typedef struct slist_node slist_node;

struct slist_node {
	void *data;
	slist_node *next;
};

slist_node *slist_node_construct(void *data, size_t size);
void slist_node_destruct(slist_node *node);

#endif /* slist_node_h */
