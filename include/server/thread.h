#ifndef THREAD_H
#define THREAD_H

#include <structs/queue.h>
#include <pthread.h>

typedef struct thread {

	unsigned int cthreads;
	unsigned short int active;

	queue *work;
	pthread_t *pool;

	pthread_mutex_t mutex;
	pthread_cond_t signal;

} thread;

typedef struct threadjob {
	void* (*task)(void *arg);
} threadjob;


// threadjob* threadjob_construct(void* (*task)(void *arg));

thread* thread_construct(unsigned int cthreads);
void thread_destruct(thread *thrd);

#endif
