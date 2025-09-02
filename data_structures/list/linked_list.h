#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../node/node.h"

struct linked_list {
	struct node *head;
	int length;

	void (*list_node_insert)(struct linked_list *linked_list, int index, void *data, int size);
	void (*list_node_remove)(struct linked_list *linked_list, int index);
	void* (*list_node_retrieve)(struct linked_list *linked_list, int index);
	void (*list_reverse)(struct linked_list *linked_list); // TODO: later maybe

};

struct linked_list linked_list_constructor(void);
void linked_list_destructor(struct linked_list *linked_list);

#endif /* LINKED_LIST_H */
