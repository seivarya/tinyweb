#include "thread_pool.h"
#include <stdio.h>
#include <stdlib.h>

void *thread_job(void *arg); //  prototype


struct thread_pool thread_pool_constructor(int num_threads) {
	
	printf("=== thread pool constructor invoked ===");
	
	struct thread_pool thread_pool;

	thread_pool.num_threads = num_threads;
	thread_pool.active = 1;
	thread_pool.pool = (pthread_t *)malloc(sizeof(pthread_t[num_threads]));

	for (int i = 0; i < num_threads; i++) {
		pthread_create(&thread_pool.pool[i], NULL, thread_job, NULL);
	}

	thread_pool.job_queue = queue_constructor();
	
	thread_pool.lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	thread_pool.signal = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

	return thread_pool;
}

void *thread_job(void *arg) {
	struct thread_pool *thread_pool = (struct thread_pool *)arg;
	
	while(thread_pool->active == 1) {

		pthread_mutex_lock(&thread_pool->lock);
		struct thread_job job = *(struct thread_job *)thread_pool->job_queue.peek(&thread_pool->job_queue);
		thread_pool->job_queue.pop(&thread_pool->job_queue);

		pthread_mutex_unlock(&thread_pool->lock);
	}


}

