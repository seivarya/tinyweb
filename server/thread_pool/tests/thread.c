#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *test(void *arg);

int main(void) {
	pthread_t thread_one;
	pthread_create(&thread_one, NULL, test, NULL);

	for (int i = 0; i < 1000; i++) {
		printf("=== iteration: %d ===\n", i);
	}

	// Wait for the thread at the end
	pthread_join(thread_one, NULL);
	printf("final statement\n");
}

void *test(void *arg) {
	int k = 0;
	for (int i = 0; i < 1000; i++) {
		k++;
		printf("\r");
	}
	printf("=== thread executed  ===\n");
	return NULL;
}

/*
removing return 0; or any other printf() statements will execute the thread even though you don't join it to main
thread. 


in code above the thread starts it's execution as soon as we create it! and when it's finished it executed and shows result instantly as long as compiler reacher _join

this time thread executed on 239 iteration ... so the thread will show it's result as soon as the thread is finished there is no such thing as waiting queue... and the only reason we use _join incase the thread takes too long and the next funcstion needs the thread's returned value...

*/
