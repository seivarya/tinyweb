#include "queue.h"


void push(struct queue *queue, void *data, int data_type);
void *pop(struct queue *queue);

void push(struct queue *queue, void *data, int data_type) {
	// int size = get_size_for_d_type(data_type); // size to allocate
	// struct node *node_to_push = create_node(data, data_type, size); 
	queue->list.insert(&queue->list, queue->list.length, data, data_type);
}

void *pop(struct queue *queue) {
	void *head_node = queue->list.retrieve(&queue->list, 0); // index 0 since it's head always.
	queue->list.remove(&queue->list, 0);
	return head_node;
}

void *peek(struct queue *queue) {
	void *head_node = queue->list.retrieve(&queue->list, 0); // index 0 since it's head always.
	return head_node; // returns head without destroying it.
}

struct queue queue_constructor(void) {
	struct queue queue;
	queue.list = linked_list_constructor();
	queue.push = push;
	queue.pop = pop; 
	queue.peek = peek;

	return queue;
}
