#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t LOCK = PTHREAD_MUTEX_INITIALIZER;

volatile long int a = 0;

void threadfunc(void *arg) {
	int loca = 0;
	pthread_mutex_lock(&LOCK);
	for (int i = 0;  i < 500000; i++) {
		a = a + i;
	}
	pthread_mutex_unlock(&LOCK);
}

void smth(void *arg) {
	int loca = 0;
	pthread_mutex_lock(&LOCK);
	for (int i = 50000;  i < 500000; i++) {
		a = a + i;
	}
	pthread_mutex_unlock(&LOCK);
}

int main() {
	pthread_t one, two;
	int i;
	a = 0;

	pthread_create(&one, NULL, (void*)&threadfunc, NULL);
	pthread_create(&two, NULL, (void*)&smth, NULL);

	pthread_join(one, NULL);
	pthread_join(two, NULL);

	printf("%d\n", a);
}
