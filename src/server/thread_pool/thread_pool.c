#include "thread_pool.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

struct thread_pool *thread_pool_constructor(int num_threads) {

	printf("=== thread_pool constructor invoked ===\n");

	struct thread_pool *tp = calloc(1, sizeof(struct thread_pool));
	if (!tp) {
		perror("calloc failed");
		return NULL;
	}

	tp->num_threads = num_threads;
	tp->active = 1;
	tp->job_queue = queue_constructor();

	printf("1here\n");
	tp->pool = malloc(sizeof(pthread_t[num_threads]));
	if (!tp->pool) {
		perror("malloc failed");
		free(tp);
		return NULL;
	}

	pthread_mutex_init(&tp->lock, NULL);
	pthread_cond_init(&tp->signal, NULL);

	printf("22here\n");

	for (int i = 0; i < tp->num_threads; i++) {
		pthread_create(&tp->pool[i], NULL, generic_thread_func, tp);
	}

	tp->add_job = add_job;

	printf("3here\n");

	return tp;
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

void test_func(struct thread_pool *thread_pool) {
	for (int i = 0; i < thread_pool->num_threads; i++) {
		pthread_create(&thread_pool->pool[i], NULL, generic_thread_func, &thread_pool); 
	}
}

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
