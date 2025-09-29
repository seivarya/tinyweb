#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *task_one(void *arg);

int main(void) {
	pthread_t thread_one;
	pthread_create(&thread_one, NULL, task_one, NULL);

	for (int i = 0; i < 10; i++) {
		printf("=== task: %d ===\n", i);
		if (i == 4) {
			pthread_join(thread_one, NULL);
		}
	}

	return 0;
}

void *task_one(void *arg) {
	printf("=== task one executed ===\n");
	return NULL;
}
