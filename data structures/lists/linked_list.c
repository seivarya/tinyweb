#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

struct node_int *create_node_int(int data); // declarations
void destroy_node_int(struct node_int *node_to_destroy);

struct node_int *iterate_int(int index, struct linked_list_int *linked_list);

void insert_node_int(int index, int data, struct linked_list_int *linked_list);
void remove_node_int(int index, struct linked_list_int *linked_list);
int retrieve_data_int(int index, struct linked_list_int *linked_list);

struct linked_list_int linked_list_int_constructor() { // contructor
	struct linked_list_int new_list;

	new_list.head = NULL;
	new_list.length = 0;

	new_list.insert = insert_node_int;
	new_list.remove = remove_node_int;
	new_list.retrieve = retrieve_data_int;
	new_list.constructor = linked_list_int_constructor;
	
	printf("linked_list_int_contructor invoked");

	return new_list;
}

struct node_int *create_node_int(int data) {
	struct node_int *new_node_address = (struct node_int *)malloc(sizeof(struct node_int));

	if (!new_node_address) {
		printf("allocation failed\n");
		exit(1);
	}

	new_node_address->data = data;
	new_node_address->next = NULL;

	return new_node_address;
}

void destroy_node_int(struct node_int *node_to_destroy) {
	free(node_to_destroy);
}

struct node_int *iterate_int(int index, struct linked_list_int *linked_list) {
	if (index < 0 || index >= linked_list->length) {
		printf("index out of bounds.\n");
		exit(9);
	}

	struct node_int *cursor = linked_list->head;
	for (int i = 0; i < index; i++) {
		cursor = cursor->next;
	}
	return cursor;
}

void insert_node_int(int index, int data, struct linked_list_int *linked_list) {

	struct node_int *node_to_insert = create_node_int(data);
	struct node_int *cursor = iterate_int(index - 1, linked_list);

	node_to_insert->next = cursor->next;
	cursor->next = node_to_insert;
}

void remove_node_int(int index, struct linked_list_int *linked_list) {
	struct node_int *cursor = iterate_int(index - 1, linked_list);
	struct node_int *node_to_remove = cursor->next;
}
















