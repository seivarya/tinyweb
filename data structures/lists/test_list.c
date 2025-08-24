#include "linked_list.h"
#include <stdio.h>

//NOTE: simple tests. totally GPT by the way.

int main(void) {
	struct linked_list_int list = linked_list_int_constructor();

	printf("=== Inserting elements ===\n");
	for (int i = 0; i < 5; i++) {
		list.insert(i, i + 1, &list);  // insert 1,2,3,4,5 at end
	}

	// Insert at head
	list.insert(0, 100, &list);  // list: 100,1,2,3,4,5
	// Insert in middle
	list.insert(3, 200, &list);  // list: 100,1,2,200,3,4,5
	// Insert at tail
	list.insert(list.length, 300, &list); // append 300

	printf("=== List after insertions ===\n");
	for (int i = 0; i < list.length; i++) {
		printf("Index %d: %d\n", i, list.retrieve(i, &list));
	}

	printf("=== Removing elements ===\n");
	// Remove head
	list.remove(0, &list); // removes 100
	// Remove middle
	list.remove(2, &list); // removes 200
	// Remove tail
	list.remove(list.length - 1, &list); // removes 300

	printf("=== List after removals ===\n");
	for (int i = 0; i < list.length; i++) {
		printf("Index %d: %d\n", i, list.retrieve(i, &list));
	}

	printf("=== Testing retrieval edge cases ===\n");
	if (list.length > 0)
		printf("Retrieve head: %d\n", list.retrieve(0, &list));
	if (list.length > 1)
		printf("Retrieve last: %d\n", list.retrieve(list.length - 1, &list));

	// Invalid index
	printf("Attempting invalid retrieval...\n");
	list.retrieve(100, &list); // should print error and exit

	return 0;
}
