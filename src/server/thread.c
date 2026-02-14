#define _MULTI_THREADED

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <server/thread.h>
#include <structs/queue.h>

void *threadjob_construct(void *arg);

void *temp(void *args);

void *temp(void *args) {
	return NULL;
}

thread* thread_construct(unsigned int cthreads) {
	if (cthreads == 0) return NULL;
	thread* thrd = malloc(sizeof(thread));
	thrd->pool = (pthread_t *)malloc(sizeof(pthread_t)); // ??
	
	if (!thrd || !thrd->pool) {
		printf("==+ malloc failed+==\n");
		exit(3);
	}

	for (unsigned int i = 0; i < cthreads; i++) {
		pthread_create(&thrd->pool[i], NULL, temp, NULL); // temp?
		
	}

	thrd->work = queue_construct();
	thrd->active = 1;

	thrd->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	thrd->signal = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

	return thrd;
}

void *threadjob_construct(void *arg) {
	thread *thrd = (thread*)arg;
	while(thrd->active == 1) {
		pthread_mutex_lock(&thrd->mutex);

		threadjob *job = (threadjob *)get_front(thrd->work);
		if (!job) {
			printf("==+ job empty +==\n");
			break;
		}
		pthread_mutex_unlock(&thrd->mutex);
	}
	return arg; // ??
}

void thread_destruct(thread *thrd) {
	if (!thrd) return;
	free(thrd);
}


