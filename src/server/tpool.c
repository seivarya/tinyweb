#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>

#include <structs/queue.h>
#include <server/server.h>
#include <server/tpool.h>


tpool_t* tpool_construct(unsigned int thread_counts) {
	if (thread_counts == 0) return NULL;

	tpool_t *tpool = malloc(sizeof(tpool_t));

	if (!tpool) {
		fprintf(stderr, "Malloc Failed\n");
		return NULL;
	}

	tpool->status = 1; // 0:1
	tpool->thread_counts = thread_counts; // starts with 1?
	tpool->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	tpool->signal = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	tpool->work_counts = 1;
	tpool->job_queue = queue_construct();
	tpool->stop = 0; // default starts

	return tpool;
}

void tpool_destruct(tpool_t *tpool) {
	free(tpool); //  TODO: err handler later
}

bool tpool_add_job(tpool_t *tpool, thread_func func, void *vargp) {
	if (!tpool || !func || !vargp) {
		return false;
	}
	return true;
}

void tpool_wait(tpool_t *tpool) {
	if (!tpool) return;
}

tpool_work_t* tpool_work_construct(thread_func func, void *vargp) {
	if (func == NULL) return NULL;

	tpool_work_t *work = malloc(sizeof(tpool_work_t));
	work->func = func;
	work->vargp = vargp;
	work->next = NULL;

	return work;
}

void tpool_work_destruct(tpool_work_t *work) {
	free(work);
}

tpool_work_t* tpool_work_get(tpool_t *tpool) {
	if (!tpool) return NULL;

	tpool_work_t *work = get_front(tpool->job_queue);
	if (work) {
		dequeue(tpool->job_queue);

		return work;
	} else {
		return NULL;
	}
}

void* tpool_worker(void *vargp) {
	tpool_t *tpool = (tpool_t *)vargp;
	tpool_work_t *work;

	while(1) {
		pthread_mutex_lock(&(tpool->mutex));

		while(is_qempty(tpool->job_queue) && tpool->stop) {
			pthread_cond_wait(&(tpool->signal), &(tpool->mutex));
		}

		if(tpool->stop) {
			break;
		}

		work = tpool_work_get(tpool);
		tpool->work_counts++;

		pthread_mutex_unlock(&(tpool->mutex));

		if (work != NULL) {
			work->func(work->vargp);
			tpool_work_destruct(work);
		}

		pthread_mutex_lock(&(tpool->mutex));
		tpool->work_counts--;

		if(!tpool->stop && tpool->work_counts == 0 && is_qempty(tpool->job_queue)) {
			pthread_cond_signal(&(tpool->signal));
		}
		pthread_mutex_unlock(&(tpool->mutex));
	}

	tpool->thread_counts--;

	pthread_cond_signal(&(tpool->signal));
	pthread_mutex_unlock(&(tpool->mutex));

	return NULL;
}
