#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node {
	void *data;
	struct node *next;
	struct node *previous; // as long as no one touches this in linked list, queue implementation it won't have any effect.
};

struct node node_constructor(void *data, int size);
void node_destructor(struct node *node);

#endif /* NODE_H */

