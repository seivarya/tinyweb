#ifndef TPOOL_H
#define TPOOL_H

#include <stdbool.h>
#include <stddef.h>
#include <pthread.h>

#include <structs/queue.h>
#include <server/server.h>

typedef void (*thread_func_t)(void *vargp);

struct tpool {
	queue 			*work_queue;
	pthread_mutex_t		work_mutex;
	pthread_cond_t		work_cond;
	pthread_cond_t 		working_cond;
	size_t 			working_cnt;
	size_t 			thread_cnt;
	bool 			stop;
};

typedef struct tpool tpool_t;

struct tpool_work {
	thread_func_t 		func;
	void 			*vargp;
	struct tpool_work 	*next;
};

typedef struct tpool_work tpool_work_t;


tpool_t *tpool_construct(size_t num);
void tpool_destruct(tpool_t *tm);

tpool_work_t *tpool_work_construct(thread_func_t func, void *vargp);
void tpool_work_destruct(tpool_work_t *work);

tpool_work_t *tpool_work_get(tpool_t *tm);
void* tpool_worker(void *vargp);

bool tpool_add_work(tpool_t *tm, thread_func_t func, void *vargp); // add work to queue
void tpool_wait(tpool_t *tm); // blocks until all work has been completed

#endif
