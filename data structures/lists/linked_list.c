#include "linked_list.h"


struct node_int *create_node_int(void);
void destroy_node_int(struct node_int *node_to_destroy);

struct node_int *iterate(int index, struct linked_list_int *linked_list);

void insert_node_int(int index, int data, struct linked_list_int *linked_list);
void remove_node_int(int index, struct linked_list_int *linked_list);
int retrieve_data_int(int index, struct linked_list_int *linked_list);




struct linked_list_int linked_list_contructor() {
	struct linked_list_int new_list;
	new_list.head = NULL;
	new_list.length = 0;

	new_list.insert = insert_node_int;
	new_list.remove = remove_node_int;
	new_list.retrieve = retrieve_data_int;


	return new_list;
}




