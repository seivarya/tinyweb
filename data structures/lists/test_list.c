#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>



int main(void) {
	struct linked_list list = linked_list_constructor();

	printf("==== inserting elements ====\n");
	// insert 1..10 at end
	for (int i = 0; i < 10; i++) {
		int *value = malloc(sizeof(int)); // since data is void* type we've to manually do this.
		*value = i + 1;
		list.insert(i, value, &list);
	}
	printf("\n");

	// insert at head
	int *head_value = malloc(sizeof(int));
	*head_value = 69;
	list.insert(0, head_value, &list);

	// insert in middle
	int *middle_value = malloc(sizeof(int));
	*middle_value = 23;
	list.insert(4, middle_value, &list); // at index 4

	// insert at tail
	int *tail_value = malloc(sizeof(int));
	*tail_value = -10;
	list.insert(list.length, tail_value, &list); // last index

	printf("==== list after insertions ====\n");

	for (int i = 0; i < list.length; i++) {
		int *value = (int *) list.retrieve(i, &list);
		printf("index %d:: %d\n", i, *value);
	}

	printf("==== removing elements ====\n");

	// remove head
	list.remove(0, &list, 1); // remove 100
	list.remove(4, &list, 1); // remove middle value
	list.remove(list.length - 1, &list, 1); // remove last index
	printf("==== list after removals ====\n");
	for (int i = 0; i < list.length; i++) {
		int *value = (int *) list.retrieve(i, &list);
		printf("index %d:: %d\n", i, *value);
	}


	printf("==== testing retrieval edge cases ====\n");
	if (list.length > 0) {
		int *val = (int*) list.retrieve(0, &list);
		printf("retrieve head: %d\n", *val);
	}
	if (list.length > 1) {
		int *val = (int*) list.retrieve(list.length - 1, &list);
		printf("retrieve last: %d\n", *val);
	}

	printf("==== cleaning up remaining nodes ====\n");
	while (list.length > 0) {
		list.remove(0, &list, 1); // each remove frees node->data too
	}

	printf("all nodes removed successfully.\n");

	return 0;
}
