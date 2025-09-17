#include "linked_list.h"
#include <stdlib.h>

struct node *create_node_list(void *data, int size);

struct node *iterate_list(int index, struct linked_list *linked_list);

void insert_node(struct linked_list *linked_list, int index, void *data, int size);
void remove_node(struct linked_list *linked_list, int index);
void *retrieve_node(struct linked_list *linked_list, int index);

struct linked_list linked_list_constructor(void) {
	struct linked_list list;
	list.head =  NULL;
	list.length = 0;

	list.list_node_insert= insert_node;
	list.list_node_remove = remove_node;
	list.list_node_retrieve = retrieve_node;

	return list;
};

void linked_list_destructor(struct linked_list *linked_list) {
	for (int i = 0; i < linked_list->length; i++) {
		linked_list->list_node_remove(linked_list, 0); 
	}
}

struct node *create_node_list(void *data, int size) { 
	struct node *new_node = malloc(sizeof(struct node));
	*new_node = node_constructor(data, size); // uses the node constructor to check dtype and assign

	return new_node;
}

struct node *iterate_list (int index, struct linked_list *linked_list) {
	if (index < 0 || index >= linked_list->length) {
		exit(9);
	}

	struct node *cursor = linked_list->head;
	
	for (int i = 0; i < index; i++) {
		cursor = cursor->next;
	}
	
	return cursor;
}

void insert_node (struct linked_list *linked_list, int index, void *data, int size) {
	struct node *node_to_insert = create_node_list(data, size);

	if (index == 0) {
		node_to_insert->next = linked_list->head;
		linked_list->head = node_to_insert;
	} else {
		struct node *cursor = iterate_list(index - 1, linked_list);
		node_to_insert->next = cursor->next;
		cursor->next = node_to_insert;
	}

	linked_list->length++;
}

void remove_node (struct linked_list *linked_list, int index) {
	struct node *node_to_remove;

	if (index == 0) {
		node_to_remove = linked_list->head;
		linked_list->head = linked_list->head->next;
	} else {
		struct node *cursor = iterate_list(index - 1, linked_list);
		node_to_remove = cursor->next;
		cursor->next = node_to_remove->next;
	}

	node_destructor(node_to_remove);
	linked_list->length--;
}

void *retrieve_node(struct linked_list *linked_list, int index) {
	struct node *node_to_retrieve;
	
	if (index == 0) {
		return linked_list->head;
	} else {
		node_to_retrieve = iterate_list(index, linked_list);
		return node_to_retrieve;
	}
} /* LINKED_LIST_C */
