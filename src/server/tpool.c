#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>

#include <structs/queue.h>
#include <server/server.h>
#include <server/tpool.h>


tpool_t *tpool_construct(size_t num) {
	if (num == 0) return NULL;
	tpool_t 	*tm;
	pthread_t	thread;

	tm = calloc(1, sizeof(*tm));
	tm->thread_cnt = num;

	pthread_mutex_init(&(tm->work_mutex), NULL);
	pthread_cond_init(&(tm->work_cond), NULL);
	pthread_cond_init(&(tm->working_cond), NULL);

	for (size_t i = 0; i < num; i++) {
		if(!pthread_create(&thread, NULL, tpool_worker, tm)) {
			fprintf(stdout, "THREAD CREATED: INST::%d\n", i);
			if (!pthread_detach(thread)) {
				fprintf(stdout, "THREAD DETACHED: INST::%d\n", i);
			}
		}
	}

	return tm;
}

void tpool_destruct(tpool_t *tm) {

	if (tm == NULL) {
		return;
	}

	queue_destruct(tm->work_queue);

	pthread_mutex_lock(&(tm->work_mutex));
	tm->stop = true;
	pthread_cond_broadcast(&(tm->work_cond));
	pthread_mutex_unlock(&(tm->work_mutex));

	tpool_wait(tm);

	pthread_mutex_destroy(&(tm->work_mutex));
	pthread_cond_destroy(&(tm->work_cond));
	pthread_cond_destroy(&(tm->working_cond));

	free(tm);
}

tpool_work_t *tpool_work_construct(thread_func_t func, void *vargp) {
	tpool_work_t *work;
	if (func == NULL)
		return NULL;
	work	= malloc(sizeof(*work));
	work->func = func;
	work->vargp = vargp;
	work->next = NULL;
	return work;
}

void tpool_work_destruct(tpool_work_t *work) {
	if (work == NULL)
		return;
	free(work);
}

tpool_work_t *tpool_work_get(tpool_t *tm) {
	tpool_work_t *work;
	work = get_front(tm->work_queue); // casting issues? 
	return work;
}

void* tpool_worker(void *vargp) {
	if (!vargp)
		return NULL;

	tpool_t		*tm = vargp;
	tpool_work_t	*work;

	while(1) {

		pthread_mutex_lock(&(tm->work_mutex));

		while(is_qempty(tm->work_queue) && !tm->stop)
			pthread_cond_wait(&(tm->work_cond), &(tm->work_mutex));
		
		if (tm->stop)
			break;

		work = tpool_work_get(tm);
		tm->working_cnt++;
		pthread_mutex_unlock(&(tm->work_mutex)); // pull the work and unlock the mutex so everything happens parallely

		if(work != NULL) {
			work->func(work->vargp);
			tpool_work_destruct(work);
		}
		pthread_mutex_lock(&(tm->work_mutex));
		tm->working_cnt--;

		if (!tm->stop && tm->working_cnt == 0 && is_qempty(tm->work_queue))
			pthread_cond_signal(&(tm->working_cond));
		pthread_mutex_unlock(&(tm->work_mutex));
	}

	tm->thread_cnt--;
	pthread_cond_signal(&(tm->working_cond));
	pthread_mutex_unlock(&(tm->work_mutex));

	return NULL;
}

bool tpool_add_work(tpool_t *tm, thread_func_t func, void *vargp) { // add work to queue
	if(!tm || !func || !vargp) { return false; }
	tpool_work_t *work = tpool_work_construct(func, vargp);
	if (work == NULL)
		return false;
	pthread_mutex_lock(&(tm->work_mutex));
	enqueue(tm->work_queue, work, sizeof(tpool_work_t));

	pthread_cond_broadcast(&(tm->work_cond));
	pthread_mutex_unlock(&(tm->work_mutex));

	return true;
}
void tpool_wait(tpool_t *tm) { // blocks until all work has been completed
	if(!tm) return;

	pthread_mutex_lock(&(tm->work_mutex));
	while (
		!is_qempty(tm->work_queue) ||
		tm->working_cnt != 0 ||
		(tm->stop && tm->thread_cnt != 0)
	) {
		pthread_cond_wait(&(tm->working_cond), &(tm->work_mutex));
	} else {
		break;
	}

pthread_mutex_unlock(&(tm->work_mutex));

}
