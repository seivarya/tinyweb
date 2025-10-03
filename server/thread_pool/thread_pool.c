#include "thread_pool.h"
#include <stdio.h>
#include <stdlib.h>

void *thread_job(void *arg); //  prototype
void add_job(struct thread_pool *thread_pool, struct thread_job thread_job);


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

	thread_pool.add_job = add_job;

	return thread_pool;
}

void thread_pool_destructor(struct thread_pool *thread_pool) {
	thread_pool->active = 0; //  INFO: once thread finish task. they can stop running
	
	for(int i = 0; i < thread_pool->num_threads; i++) {
		pthread_cond_signal(&thread_pool->signal);
	}
	
	for(int i = 0; i < thread_pool->num_threads; i++) {
		pthread_join(thread_pool->pool[i], NULL);
	}
	free(thread_pool->pool);

	queue_destructor(&thread_pool->job_queue);
	printf("=== thread_pool destroyed succesfully ===\n");

}

struct thread_job thread_job_constructor(void *(*job)(void *arg), void *arg) {

	struct thread_job thread_job;

	thread_job.job_exec_func = job;
	thread_job.arg = arg;

	return thread_job;
}


void *thread_job(void *arg) {

	struct thread_pool *thread_pool =  (struct thread_pool *)arg;

	printf("=== thread_pool created ===\n");
	while(thread_pool->active == 1) {

		pthread_mutex_lock(&thread_pool->lock); //  INFO: this will lock our thread

		printf("=== mutex lock initiated, resource locked ===\n");
		while((thread_pool->job_queue.is_empty(&thread_pool->job_queue) == 1) && (thread_pool->active == 1)) {
			printf("=== job is empty! waiting for job to fill or active status to change  ===\n");

			pthread_cond_wait(&thread_pool->signal, &thread_pool->lock);
		}

		// critical section start

		struct thread_job job = *(struct thread_job *)thread_pool->job_queue.peek(&thread_pool->job_queue);
		thread_pool->job_queue.pop(&thread_pool->job_queue);

		// critical section end

		pthread_mutex_unlock(&thread_pool->lock);

		printf("=== mutex unlocked successfully  ===\n");

		if (job.job_exec_func) {
			printf("=== job found! ===\n");
			job.job_exec_func(job.arg);
		}
	}
	return NULL; //  INFO: we don't need anything out of the loop! we just want the execution
}

void add_job(struct thread_pool *thread_pool, struct thread_job thread_job) {
	thread_pool->job_queue.push(&thread_pool->job_queue, &thread_job, sizeof(thread_job)); //  FIX: maybe sizeof (thread_job) is incorrect !?
}

/* 

pthread_mutex_lock() locks ours thread: the thread calls pthread_mutex_lock to acquire ownership of the mutex. this is the 
entry gate to the critical section. if another thread holds the mutex, this thread's execution is suspended by the os
scheduler. it is placed in a wait queue for this specific mutex and consumes no CPU resourcs until the mutex is released.
...
pthread_cond_wait(): it is designed to be only called after a thread has already acquired a mutex. it performs threee steps
atomically (as one single, uninterruptible operation)

...

	step 1: unlocks the mutex > it releases the lock that was acquired in the previous step. it prevents deadlock by
	allowing other threads (specifically, a "producer" thread that adds jobs) to acquire the mutex and modify the
	shared resource.
	...
	step 2: blocks the thread > it suspends the current thread's execution.
	...
	step 3: waits for the condition variable > it places the thread in a queue of threads waiting for the condition variable (signal) to be signaled.

...

when another thread calls pthread_cond_signal(), this thread wakes up. upon waking it does not immediately proceed.
it must first wait to re-acquire the mutex before pthread_cond_wait can return. this ensures that when the thread
continues, it once again has exclusive access to the shared resource.
...
struct thread_job job = *(struct thread_job *)thread_pool->job_queue.peek(&thread_pool->job_queue);
thread_pool->job_queue.pop(&thread_pool->job_queue): at this point, the thread has successfully woken up and reacquired the
mutex. it is now executing inside the critical section. it can safely interact with the job_queue.
...
pthread_mutex_unlock: realeases the mutex
pthread_mutex_lock makes threads wait.

...

while((thread_pool->job_queue.is_empty(&thread_pool->job_queue) == 1) && (thread_pool->active)) {
    pthread_cond_wait(&thread_pool->signal, &thread_pool->lock);
}

checks two things: first, whether the job queue is empty. If it is, there’s nothing for the thread to do right now. Second, it checks whether the thread pool is still active. If it is active, it means more jobs might come in soon,
so instead of exiting, the thread waits safely using pthread_cond_wait. This function puts the thread to sleep without wasting CPU, and while sleeping it releases the mutex, allowing other threads or the main thread to add new jobs
When a job arrives and the thread is signaled, it wakes up and automatically re-acquires the mutex, then checks the queue again. If the pool is not active, the thread knows no more jobs will come and can exit cleanly.
*/
