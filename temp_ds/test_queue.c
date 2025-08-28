#include "queue.h"
#include <stdio.h>
#include <stdbool.h>

int main(void) {
	struct queue queue = queue_constructor();
	printf("=== queue constructed ===\n");

	printf("=== pushing values ===\n");
	for (int i = 0; i < 10; i++) {
		int array[5] = {i, i * 2, i + 21, i - 2, i ^ 2};
		queue.push(&queue, array, Int, 5);
	}

	// printing entire queue

	printf("\n=== full queue before pop ===\n");
	for (int i = 0; i < queue.list.length; i++) {
		struct node *n = (struct node *)queue.list.retrieve(&queue.list, i);
		printf("index %d: <", i);
		for (int j = 0; j < n->size; j++) {
			if (j > 0) printf(", ");
			printf("%d", ((int *)n->data)[j]);
		}
		printf("> -> \n");
	}
	printf("\n");
	// peeking 
	
	printf("\n=== peeked values at head ===\n");
	struct node *head_node = (struct node *)queue.peek(&queue);
	printf("head node: < ");
	for (int j = 0; j < head_node->size; j++) {
		if (j > 0) printf(", ");
		printf("%d", ((int *)head_node->data)[j]);
	}
	printf(" >\n");

	// pop test
	
	printf("\n=== popping 3 nodes ===\n");
	for (int k = 0; k < 3; k++) {
		queue.pop(&queue);
		if (queue.list.length > 0) {
			head_node = (struct node *)queue.peek(&queue);
			printf("new head: < ");
			for (int j = 0; j < head_node->size; j++) {
				if (j > 0) printf(", ");
				printf("%d", ((int *)head_node->data)[j]);
			}
			printf(" >\n");
		} else {
			printf("queue is now empty\n");
		}
	}

	printf("=== destroying queue ===");
	queue_destructor(&queue);

	return 0;
}
