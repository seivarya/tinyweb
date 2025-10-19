#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "../../data_structures/queue/queue.h"
#include <pthread.h>

struct thread_job {  //  INFO: job_queue will have thread_job structs and the jobs can be of diff/ type since it's generic
	void *(*job_exec_func)(void *arg);
	void *arg;
};

struct thread_job thread_job_constructor(void *(*job_exec_func)(void *arg), void *arg);

/* === :: ==== ==== :: ==== */

struct thread_pool {

	int num_threads; //  INFO: number of threads
	
	short int active; //  INFO: will store only 2 states [active, inactive] 1, 0
	
	struct queue job_queue; //  INFO: this'll work based off on FIFO principle
	
	pthread_t *pool; // INFO:  array of thread of unknown size 
	pthread_mutex_t lock; //  INFO: this will prevent from 2 processes accessing the same resource at the same time.
	pthread_cond_t signal; //  INFO: so that we can reduce the thread's impact on system. since our thread will keep checking queue in infinite loop.
	
	void (*add_job)(struct thread_pool *thread_pool, struct thread_job thread_job);
};

struct thread_pool *thread_pool_constructor(int num_threads);
void thread_pool_destructor(struct thread_pool *thread_pool);

void thread_pool_start(struct thread_pool *thread_pool); 
void add_job(struct thread_pool *thread_pool, struct thread_job thread_job);
void *generic_thread_func(void *arg);


void test_func(struct thread_pool *thread_pool);

#endif /* THREAD_POOL_H */
