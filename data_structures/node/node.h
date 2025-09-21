#ifndef NODE_H
#define NODE_H

//  INFO: node object initialization

struct node {
	void *data;
	struct node *next;
	struct node *previous; //  WARNING:  as long as no one touches this in linked list, the queue implementation won't have any issues.
};

//  INFO: methods

struct node node_constructor(void *data, int size);
void node_destructor(struct node *node);

#endif /* NODE_H */
