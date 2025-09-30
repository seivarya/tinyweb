#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *val_returner(void *arg);

int main(void) {
	pthread_t thread;
	void *returned_val;

	pthread_create(&thread, NULL, &val_returner, NULL);
	for(int i = 0; i < 100; i++) {
		printf("\r");
	}
	pthread_join(thread, &returned_val);
	printf("value returned: %s\n", (char *)(returned_val));
	free(returned_val);
	return 0;
}


void *val_returner(void *arg) {
	char *value = malloc(100); // allocate on heap instead of stack

	for (int i = 0; i < 100000; i++) {
		printf("\r");
	}
	int val_check = sprintf(value,  "this is the value that's returned to user");
	if (val_check > 0) {
		printf("fine\n");
	}else {
		printf("error\n");
		exit(1);
	}
	return value;
}

//  WARNING: allocating the memory on stack instead of heap will cause segfault.
//  why? well becauese each worker function + main function have their own stack frame and when a function
//  returns a value the stack frame gets popped ! that means it's no longer valid and our function returns
//  a pointer to that stack frame and if it's invalid it'll obv crash! why?
//  c functions can't return pointer to values that live on stack because initializing values on stack will
//  automatically initialize that value on local stack which dies after functions returns value.. that's why it's
//  important to use malloc which initializes value ptr on heap
