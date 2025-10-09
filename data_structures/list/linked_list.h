// linked_list.h > definition of linked_list struct and it's method

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../node/node.h"

//  INFO: linked list object initialization

struct linked_list {
	struct node *head;
	int length;

	void (*list_node_insert)(struct linked_list *linked_list, int index, void *data, int size);
	void (*list_node_remove)(struct linked_list *linked_list, int index);
	void* (*list_node_retrieve)(struct linked_list *linked_list, int index);
	void (*list_reverse)(struct linked_list *linked_list); //  TODO: later maybe
};

//  INFO: methods

struct linked_list linked_list_constructor(void);
void linked_list_destructor(struct linked_list *linked_list);

//  INFO: function prototypes

struct node *create_node_list(void *data, int size);
struct node *iterate_list(int index, struct linked_list *linked_list);

void insert_node(struct linked_list *linked_list, int index, void *data, int size);
void remove_node(struct linked_list *linked_list, int index);
void *retrieve_node(struct linked_list *linked_list, int index);

#endif /* LINKED_LIST_H */
