#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../node/node.h"
#include <stdlib.h>



struct linked_list_int {
	struct node_int *head;
	int length;
	

	void (*insert)(int index, int data, struct linked_list_int *linked_list);
	void(*remove)(int index, struct linked_list_int *linked_list);
	int (*retrieve)(int index, struct linked_list_int *linked_list);

};
#endif
