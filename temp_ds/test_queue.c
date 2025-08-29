#include <stdio.h>
#include "queue.h"

int main(void) {
	struct queue queue = queue_constructor();

	printf("=== pushing single ints ===\n");
	int a = 100;
	queue.push(&queue, &a, sizeof(a));

	int b = 200;
	queue.push(&queue, &b, sizeof(b));

	int c = 300;
	queue.push(&queue, &c, sizeof(c));

	printf("=== peeking head ===\n");
	struct node *head = (struct node *)queue.peek(&queue);
	printf("head: %d\n", *(int *)head->data);

	printf("=== pushing array ===\n");
	int arr[5] = {10, 20, 30, 40, 50};
	queue.push(&queue, &arr, sizeof(arr));

	printf("=== print queue ===\n");
	for (int i = 0; i < queue.list.length; i++) {
		struct node *n = queue.list.retrieve(&queue.list, i);

		// determine if it's single int or array based on size (simplified)
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

	printf("=== popping head ===\n");
	queue.pop(&queue);

	printf("=== new head ===\n");
	head = (struct node *)queue.peek(&queue);
	printf("new head using peek: %d\n", *(int *)head->data);

	printf("=== print queue after pop ===\n");
	for (int i = 0; i < queue.list.length; i++) {
		struct node *n = queue.list.retrieve(&queue.list, i);

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

	queue_destructor(&queue);

	return 0;
}
