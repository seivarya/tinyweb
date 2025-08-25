#ifndef QUEUE_H
#define QUEUE_H

#include "../node/node.h"
#include "../lists/linked_list.h"

struct queue {
	struct linked_list list;
	
	void (*push)(void *data, struct queue *queue);
	void* (*pop)(struct queue *queue);
};

struct queue queue_constructor(void);

#endif
