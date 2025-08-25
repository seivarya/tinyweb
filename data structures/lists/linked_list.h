#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../node/node.h"
#include <stdlib.h>

struct linked_list {
	struct node *head;
	int length;

	void (*insert)(int index, void *data, struct linked_list *linked_list);
	void(*remove)(int index, struct linked_list *linked_list, int free_node);
	void* (*retrieve)(int index, struct linked_list *linked_list);
};

struct linked_list linked_list_constructor();
#endif
