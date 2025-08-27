#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>


struct queue {
	struct linked_list list;
	
	void (*push)(struct queue *queue, void *data, int data_type);
	void* (*pop)(struct queue *queue); // destroys the head node.
	void* (*peek)(struct queue *queue); // returns head without destroying it 
};

struct queue queue_constructor(void);

#endif
