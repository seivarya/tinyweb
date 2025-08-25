#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

struct node *create_node (void *data);
void destroy_node(struct node *node_to_destroy);

struct node *iterate(int index, struct linked_list *linked_list);

void insert_node(int index, void *data, struct linked_list *linked_list);
void remove_node(int index, struct linked_list *linked_list, int free_node);
void *retrieve_data(int index, struct linked_list *linked_list);

struct linked_list linked_list_constructor () {
	struct linked_list new_list;

	new_list.head = NULL;
	new_list.length = 0;

	new_list.insert = insert_node; // we sort of link the .<operation> to the function this way we avoid name conflicts and simulate more oop behaviour.
	new_list.remove = remove_node;
	new_list.retrieve = retrieve_data;

	return new_list;
}

struct node *create_node(void *data) {
	struct node *new_node_address = (struct node *)malloc(sizeof(struct node));

	if (!new_node_address) {
		printf("allocation failed\n");
		exit(1);
	}

	new_node_address->data = data;
	new_node_address->next = NULL;

	return new_node_address;
}

void destroy_node(struct node *node_to_destroy) {
	free(node_to_destroy);
}

struct node *iterate(int index, struct linked_list *linked_list) {
	if (index < 0 || index >= linked_list->length) {
		printf("index out of bounds.\n");
		exit(9);
	}

	struct node *cursor = linked_list->head;
	for (int i = 0; i < index; i++)
		cursor = cursor->next;
	return cursor;
}

void insert_node(int index, void *data, struct linked_list *linked_list) {

	struct node *node_to_insert = create_node(data);

	if (index == 0) {
		node_to_insert->next = linked_list->head;
		linked_list->head = node_to_insert;
	} else {
		struct node *cursor = iterate(index - 1, linked_list);
		node_to_insert->next = cursor->next;
		cursor->next = node_to_insert;
	}
	linked_list->length++;
}

void remove_node(int index, struct linked_list *linked_list, int free_node) {
	struct node *node_to_remove;
	if (index == 0) {
		node_to_remove = linked_list->head;
		linked_list->head = linked_list->head->next;
	} else {
		struct node *cursor = iterate(index - 1, linked_list);
		node_to_remove = cursor->next;
		cursor->next = node_to_remove->next;
	}

	if (free_node == 1) {
		free(node_to_remove->data);
	}

	destroy_node(node_to_remove);
	linked_list->length--;
}

void *retrieve_data(int index, struct linked_list *linked_list) {
	if (index < 0 || index >= linked_list->length) {
		printf("index out of bounds.\n");
		exit(1);
	}

	struct node *cursor = iterate(index, linked_list);
	return cursor->data;
}
