#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct linked_list {
	struct node *head;
	int length;

	void (*insert)(struct linked_list *linked_list, int index, void *data, int size);
	void (*remove)(struct linked_list *linked_list, int index);
	void* (*retrieve)(struct linked_list *linked_list, int index);
	void (*reverse)(struct linked_list *linked_list); // TODO: later maybe

};

struct linked_list linked_list_constructor(void);
void linked_list_destructor(struct linked_list *linked_list);

#endif /* LINKED_LIST_H */
