#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>


struct queue {
	struct linked_list list;
	
	void (*push)(void *data, struct queue *queue);
	void* (*pop)(struct queue *queue);
};

struct queue queue_constructor(void);
struct queue queue_destructor(void);

#endif
