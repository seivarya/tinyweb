#ifndef QUEUE_H
#define QUEUE_H

#include "../list/linked_list.h"

//  INFO: queue object initialization

struct queue {
	struct linked_list list;

	void (*push)(struct queue *queue, void *data, int size);
	void (*pop)(struct queue *queue);
	int (*is_empty)(struct queue *queue);
	void* (*peek)(struct queue *queue);

};

//  INFO: methods
struct queue queue_constructor(void);
void queue_destructor(struct queue *queue);

//  INFO: function prototypes

void push(struct queue *queue, void *data, int size);
void pop(struct queue *queue);
void *peek(struct queue *queue);
int is_empty(struct queue *queue);

#endif /* QUEUE_H */
