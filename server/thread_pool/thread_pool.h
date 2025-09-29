#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "../../data_structures/queue/queue.h"
#include <pthread.h>

struct thread_pool {

	int num_threads; //  INFO: number of threads
	short int active; //  INFO: will store only 2 states [active, inactive] 1:0
	
	struct queue job_queue; //  INFO: this'll work based off on FIFO principle
	
	pthread_t *pool;
	


};

#endif
