#include <stdio.h>
#include "linked_list.h"

int main(void) {
	struct linked_list list = linked_list_constructor();

	printf("=== inserting single ints ===\n");
	int a = 100;
	list.insert(&list, 0, &a, sizeof(a));  // insert at head

	int b = 200;
	list.insert(&list, 1, &b, sizeof(b));  // insert at tail

	int c = 300;
	list.insert(&list, 2, &c, sizeof(c));  // insert at tail

	printf("=== peeking head ===\n");
	struct node *head = (struct node *)list.retrieve(&list, 0);
	printf("head: %d\n", *(int *)head->data);

	printf("=== inserting array ===\n");
	int arr[5] = {10, 20, 30, 40, 50};
	list.insert(&list, 3, &arr, sizeof(arr));

	printf("=== print linked list ===\n");
	for (int i = 0; i < list.length; i++) {
		struct node *n = list.retrieve(&list, i);

		// determine if it's single int or array based on index (simplified)
		if (i < 3) { // first 3 are single ints
			printf("%d: %d\n", i, *(int *)n->data);
		} else { // last is array
			int *arr_data = (int *)n->data;
			printf("%d: ", i);
			for (int j = 0; j < 5; j++) {
				printf("%d ", arr_data[j]);
			}
			printf("\n");
		}
	}

	printf("=== removing head ===\n");
	list.remove(&list, 0);

	printf("=== new head ===\n");
	head = (struct node *)list.retrieve(&list, 0);
	printf("new head: %d\n", *(int *)head->data);

	printf("=== print linked list after removing head ===\n");
	for (int i = 0; i < list.length; i++) {
		struct node *n = list.retrieve(&list, i);

		if (i < 2) { // now only 2 single ints left
			printf("%d: %d\n", i, *(int *)n->data);
		} else { // array
			int *arr_data = (int *)n->data;
			printf("%d: ", i);
			for (int j = 0; j < 5; j++) {
				printf("%d ", arr_data[j]);
			}
			printf("\n");
		}
	}

	linked_list_destructor(&list);

	return 0;
}
