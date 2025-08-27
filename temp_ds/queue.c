#include "queue.h"


void push(void *data, struct queue *queue) {}


void *pop(struct queue *queue) {}

struct queue queue_constructor(void) {
	struct queue queue;
	queue.list = linked_list_constructor();
	queue.push = push;
	queue.pop = pop; //TODO: add peek.
}

