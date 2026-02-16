#ifndef TPOOL_H
#define TPOOL_H

#include <stdbool.h>
#include <stddef.h>
#include <pthread.h>

#include <structs/queue.h>
#include <server/server.h>

typedef void (*thread_func)(void *vargp); // alias <threadfunc>

typedef struct tpool  {
	unsigned short int status;
	unsigned int thread_counts;
	unsigned int work_counts;
	pthread_mutex_t mutex;
	pthread_cond_t signal;
	queue *job_queue;
	bool stop;
} tpool_t;


typedef struct tpool_work {
	thread_func func;
	void *vargp;
	struct tpool_work *next;
} tpool_work_t;

tpool_t* tpool_construct(unsigned int thread_count);
void tpool_destruct(tpool_t *tpool);

bool tpool_add_job(tpool_t *tpool, thread_func func, void *vargp);
void tpool_wait(tpool_t *tpool);

tpool_work_t* tpool_work_construct(thread_func func, void *vargp);
void tpool_work_destruct(tpool_work_t *work);
tpool_work_t* tpool_work_get(tpool_t *tpool);

void* tpool_worker(void *vargp);

#endif


