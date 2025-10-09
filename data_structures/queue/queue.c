#include "queue.h"

//  INFO: queue constructor

struct queue queue_constructor(void) {
	struct queue queue;
	queue.list = linked_list_constructor();
	queue.push = push;
	queue.pop = pop; 
	queue.peek = peek;
	queue.is_empty = is_empty;

	return queue;
}

//  INFO: queue destructor

void queue_destructor(struct queue *queue) {
	while(queue->list.length) {
		queue->pop(queue);
	}
}

//  INFO: public methods

void push(struct queue *queue, void *data, int size) {
	queue->list.list_node_insert(&queue->list, queue->list.length, data, size);
}

void pop(struct queue *queue) {
	queue->list.list_node_remove(&queue->list, 0);
}

int is_empty(struct queue *queue) {

	if (queue->list.length <= 0 || !(queue->list.length)) {
		return 1;
	} else {
		return 0;
	}
}

void *peek(struct queue *queue) {
	struct node *node_head = queue->list.list_node_retrieve(&queue->list, 0); // index 0 since it's head always.
	return node_head; // returns head without destroying it.
} /* QUEUE_C */
