#include "queue.h"


void push(struct queue *queue, void *data, int data_type, int size);
void pop(struct queue *queue);
void *peek(struct queue *queue);


struct queue queue_constructor(void) {
	struct queue queue;
	queue.list = linked_list_constructor();
	queue.push = push;
	queue.pop = pop; 
	queue.peek = peek;

	return queue;
}

void queue_destructor(struct queue *queue) {
	linked_list_destructor(&queue->list);
}

void push(struct queue *queue, void *data, int data_type, int size) {
	queue->list.insert(&queue->list, queue->list.length, data, data_type, size);
}

void pop(struct queue *queue) {
	queue->list.remove(&queue->list, 0);
	printf("=== popped node ===\n");
}

void *peek(struct queue *queue) {
	struct node *node_head = queue->list.retrieve(&queue->list, 0); // index 0 since it's head always.
	return node_head; // returns head without destroying it.
}

