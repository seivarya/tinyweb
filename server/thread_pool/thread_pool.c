#include "thread_pool.h"
#include <stdio.h>
#include <stdlib.h>

void add_job(struct thread_pool *thread_pool, struct thread_job thread_job);
void *generic_thread_func(void *arg);

struct thread_pool thread_pool_constructor(int num_threads) {

	printf("=== thread_pool constructor invoked ===\n");

	struct thread_pool thread_pool;

	thread_pool.num_threads = num_threads;
	thread_pool.active = 1;
	thread_pool.job_queue = queue_constructor();

	thread_pool.pool = (pthread_t *)malloc(sizeof(pthread_t[num_threads]));

	pthread_mutex_init(&thread_pool.lock, NULL); 
	pthread_cond_init(&thread_pool.signal, NULL);

	//  ISSUE: you can't use PTHREAD_MUTEX_INITIALIZER because that's for compile time initialization only! we use em outside structs and funcs and the mutex_init() is for runtime init

	for (int i = 0; i < num_threads; i++) {
		pthread_create(&thread_pool.pool[i], NULL, generic_thread_func, NULL); //  FIX: issue here.
	}

	thread_pool.add_job = add_job;

	return thread_pool;
}

void thread_pool_destructor(struct thread_pool *thread_pool) {

	thread_pool->active = 0;

	for(int i = 0; i < thread_pool->num_threads; i++) {
		pthread_cond_signal(&thread_pool->signal);
	}

	for(int i = 0; i < thread_pool->num_threads; i++) {
		pthread_join(thread_pool->pool[i], NULL);
	}

	free(thread_pool->pool);
	queue_destructor(&thread_pool->job_queue);

	printf("=== thread_pool destructed successfully ===\n");
}

// cont

void add_job(struct thread_pool *thread_pool, struct thread_job thread_job) {
	thread_pool->job_queue.push(&thread_pool->job_queue, &thread_job, sizeof(thread_job));
}

void *generic_thread_func(void *arg) {

	struct thread_pool *thread_pool = (struct thread_pool *)arg;

	while(thread_pool->active == 1) {

		pthread_mutex_lock(&thread_pool->lock);

		while(thread_pool->job_queue.is_empty(&thread_pool->job_queue) == 1 && thread_pool->active == 1) {
			printf("=== job queue is empty, waiting for new jobs to enter/ pushed ===\n");
			pthread_cond_wait(&thread_pool->signal, &thread_pool->lock);
		}
		// critical section start

		struct thread_job job = *(struct thread_job *)thread_pool->job_queue.peek(&thread_pool->job_queue);
		thread_pool->job_queue.pop(&thread_pool->job_queue);

		// critical section end

		pthread_mutex_unlock(&thread_pool->lock);

		printf("=== mutex unlocked succesfully ===\n");

		if (job.job_exec_func) {
			printf("=== job exec funcion found ===\n");
			job.job_exec_func(job.arg);
		}
	}

	return NULL;
}


