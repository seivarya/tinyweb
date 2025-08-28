#include "linked_list.h"
#include <stdio.h>
#include <stdbool.h>

int main(void) {
	struct linked_list list = linked_list_constructor();
	printf("=== linked list constructed ===\n");

	// single element nodes

	int a = 10;
	list.insert(&list, 0, &a, Int, 1);

	float b = 10.32f;
	list.insert(&list, 1, &b, Float, 1);

	bool c = true;
	list.insert(&list, 2, &c, Bool, 1);

	printf("=== single element nodes ===\n");
	struct node *int_single_node = (struct node *)list.retrieve(&list, 0);
	printf("index 0: %d\n", *(int *)int_single_node->data);

	struct node *float_single_node = (struct node *)list.retrieve(&list, 1);
	printf("index 1: %.2f\n", *(float *)float_single_node->data);

	struct node *bool_single_node = (struct node *)list.retrieve(&list, 2);
	printf("index 2: %s\n", (*(bool *)bool_single_node->data) ? "true" : "false");

	// multi-element nodes
	
	printf("=== multi-element nodes ===\n");
	int int_array[5] = {1, 2, 4, 3, 5};
	list.insert(&list, 3, int_array, Int, 5);

	float float_array[3] = {2.2f, 42.3f, 77.5f};
	list.insert(&list, 4, float_array, Float, 3);

	bool bool_array[6] = {true, true, false, false, true, false};
	list.insert(&list, 5, bool_array, Bool, 6);

	// mixed multi + single nodes 

	long long_val = 123456789L;
	list.insert(&list, 6, &long_val, Long, 1);

	double double_array[2] = {3.14159, 2.71828};
	list.insert(&list, 7, double_array, Double, 2);

	// priting entire linked list
	
	printf("\n=== full linked list ===\n");
	for (int i = 0; i < list.length; i++) {
		struct node *node = (struct node *)list.retrieve(&list, i);
		printf("index %d: < ", i);
		for (int j = 0; j < node->size; j++) {

			if (j > 0) {
				printf(", ");
			}

			switch (node->data_type) {
				case Int:
					printf("%d", ((int *)node->data)[j]);
					break;
				case Float:
					printf("%.2f", ((float *)node->data)[j]);
					break;
				case Double:
					printf("%.5f", ((double *)node->data)[j]);
					break;
				case Char:
					printf("%c", ((char *)node->data)[j]);
					break;
				case Long:
					printf("%ld", ((long *)node->data)[j]);
					break;
				case Bool:
					printf("%s", ((bool *)node->data)[j] ? "true" : "false");
					break;
			}
		}
		printf(" >\n");
	}

	linked_list_destructor(&list);

	return 0;
}
