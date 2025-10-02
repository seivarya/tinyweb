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
	struct thread_pool *thread_pool =  (struct thread_pool *)arg;

	while(thread_pool->active == 1) {

		pthread_mutex_lock(&thread_pool->lock); //  INFO: this will lock our thread

		while((thread_pool->job_queue.is_empty(&thread_pool->job_queue) == 1) && (thread_pool->active)) {
		pthread_cond_wait(&thread_pool->signal, &thread_pool->lock);
		}

		// critical section start
	
		struct thread_job job = *(struct thread_job *)thread_pool->job_queue.peek(&thread_pool->job_queue);
		thread_pool->job_queue.pop(&thread_pool->job_queue);

		printf("=== job removed from queue and will be executed locally ===");

		// critical section end
		
		pthread_mutex_unlock(&thread_pool->lock);

		if (job.job) {
			printf("=== job found! ===\n");
			job.job(job.arg);
		}
	}
	return NULL; //  INFO: we don't need anything out of the loop! we just want the execution
}

/* 

pthread_mutex_lock() locks ours thread: the thread calls pthread_mutex_lock to acquire ownership of the mutex. this is the 
entry gate to the critical section. if another thread holds the mutex, this thread's execution is suspended by the os
scheduler. it is placed in a wait queue for this specific mutex and consumes no CPU resourcs until the mutex is released.
...
pthread_cond_wait(): it is designed to be only called after a thread has already acquired a mutex. it performs threee steps
atomically (as one single, uninterruptible operation)
...
	step 1: unlocks the mutex > it realeases the lock that was acquired in the previous step. it prevents deadlock by
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
...
> the point of pthread_cond_wait.. i thought mutex lock locks the resource for one thread and makes other threads wait.. so why cond? 

The critical difference is the REASON they are waiting.

Let's break it down.

    A Mutex (pthread_mutex_lock) makes a thread wait for PERMISSION to act.

    A Condition Variable (pthread_cond_wait) makes a thread wait because a CONDITION is not met (e.g., the thing it needs to work on doesn't exist yet).

Think of it like this:

The "Busy Toliet" Analogy

Imagine a single-person public toilet. The lock on the door is the Mutex.

Scenario 1: Using Only a Mutex

    You (Thread A) want to use the toilet. The door is unlocked.

    You go in and lock the door. You have acquired the mutex.

    Someone else (Thread B) arrives. They see the door is locked. They must wait.

    Why are they waiting? They are waiting for permission to enter. They are waiting for you to release the lock. This is what pthread_mutex_lock does. It manages the queue of people waiting for access.

    You finish, you unlock and exit. You have released the mutex.

    Thread B can now enter and lock the door.

So far, the mutex works perfectly for managing access.

Scenario 2: The New Problem a Mutex CANNOT Solve

    You (Thread A) acquire the lock and enter the toilet.

    You discover there is no toilet paper. The condition "toilet paper is available" is false.

    What do you do now?

        You cannot just wait inside the locked toilet. Why? Because the janitor (the "Producer" thread who restocks the paper) cannot get in to help you, because you are holding the lock! This is a DEADLOCK. You are waiting for the janitor, and the janitor is waiting for you.

This is the exact problem pthread_cond_wait was invented to solve. It's for when a thread has successfully gained access (it has the lock) but discovers that the state of the resource isn't right for it to do its work.

The pthread_cond_wait Solution

pthread_cond_wait is like a magic "Request Service" button inside the toilet.

When you push this button, it does two things at the same time:

    It magically unlocks the main door (releases the mutex).

    It puts you into a "hibernation" or "sleep" mode (you are now waiting on the condition variable).

Because you released the lock, the janitor (Producer Thread) can now enter, restock the paper, and then shout "All set!" (pthread_cond_signal). That signal wakes you from your sleep. When you wake up, you automatically try to lock the door again, and once you succeed, you can finally do your work because the condition "toilet paper is available" is now true.

Summary

Waiting Mechanism	Why does it wait?	Analogy
pthread_mutex_lock	Waits because another thread is currently in the critical section. It's waiting for permission to enter.	Waiting outside a locked toilet door that someone else is using.
pthread_cond_wait	Waits because it's already inside the critical section but the data is not in the right state (e.g., a queue is empty). It's waiting for the state to change.	Being inside the toilet but having to wait for a restock of toilet paper. It temporarily unlocks the door to let the janitor in.

So, you need both:

    A Mutex to protect the integrity of the resource (so two threads don't pop the same job).

    A Condition Variable to efficiently wait when the resource is protected but not ready (the job queue is empty).

*/
