#include "queue.h"

void push(void *data, struct queue *queue) {
	queue->list.insert(queue->list.length, data, &queue->list);
}

void *pop(struct queue *queue) {
	void *data = queue->list.retrieve(0, &queue->list);
	queue->list.remove(0, &queue->list, 0);
	return data;
}

struct queue queue_constructor() {
	struct queue queue;
	
	queue.list = linked_list_constructor();
	queue.push = push;
	queue.pop = pop;
	
	return queue;
}
