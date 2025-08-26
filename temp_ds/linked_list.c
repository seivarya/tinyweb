#include "linked_list.h"

struct node *create_node(void *data, int data_type, int size);

struct node *iterate(int index, struct linked_list *linked_list);

void insert_node(struct linked_list *linked_list, int index, void *data, int data_type);
void remove_node(struct linked_list *linked_list, int index);
void *retrieve_node(struct linked_list *linked_list, int index);

int get_size_for_d_type (int data_type);

struct linked_list linked_list_constructor(void) {
	struct linked_list list;
	list.head =  NULL;
	list.length = 0;

	list.insert = insert_node;
	list.remove = remove_node;
	list.retrieve = retrieve_node;

	return list;
};

struct node *create_node(void *data, int data_type, int size) { 
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	*new_node = node_constructor(data, data_type, size); // uses the node constructor to check dtype and assign
	return new_node;
}
struct node *iterate (int index, struct linked_list *linked_list) {
	if (index < 0 || index >= linked_list->length) {
		printf("=== index out of bounds ===");
		exit(9);
	}

	struct node *cursor = linked_list->head;
	for (int i = 0; i < index; i++) {
		cursor = cursor->next;
	}
	return cursor;
}

void insert_node (struct linked_list *linked_list, int index, void *data, int data_type) {
	int size = get_size_for_d_type(data_type);
	struct node *node_to_insert = create_node(data, data_type, size);

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
void remove_node (struct linked_list *linked_list, int index) {
	struct node *node_to_remove;
	if (index == 0) {
		node_to_remove = linked_list->head;
		linked_list->head = linked_list->head->next;
	} else {
		struct node *cursor = iterate(index - 1, linked_list);
		node_to_remove = cursor->next;
		cursor->next = node_to_remove->next;
	}
	node_destructor(node_to_remove);
	linked_list->length--;
}

void *retrieve_data(struct linked_list *linked_list, int index) {
	
}

int get_size_for_type(int data_type) {
	switch (data_type) {
		case Int:    return sizeof(int);
		case Float:  return sizeof(float);
		case Double: return sizeof(double);
		case Char:   return sizeof(char);
		case Long:   return sizeof(long);
		case Bool:   return sizeof(bool);
		default:
			printf("=== invalid data type ===\n");
			exit(1);
	}
}
