#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "../../data_structures/queue/queue.h"
#include <pthread.h>

struct thread_pool {

	int num_threads; //  INFO: number of threads
	short int active; //  INFO: will store only 2 states [active, inactive] 1, 0
	
	struct queue job_queue; //  INFO: this'll work based off on FIFO principle
	
	pthread_t *pool; // INFO:  array of thread of unknown size 
	pthread_mutex_t lock; //  INFO: this will prevent from 2 processes accessing the same resource at the same time.
	pthread_cond_t signal; //  INFO: so that we can reduce the thread's impact on system. since our thread will keep checking queue in infinite loop.
};

struct thead_job {
	void *(*job)(void *arg);
	void *arg;
};

struct thread_pool thread_pool_constructor(int num_threads);
struct thread_job thread_job_constructor(void *(*job)(void *arg), void *arg);

#endif


/*
INFO: why we need multi-threading? for performace but the reason we need thread pool is coz incase we don't know
how many jobs we've to execute then the CPU can be overwhelmed resulting in computer crash.
a thread_pool will define finited number of thread_pool and execute them.
*/
