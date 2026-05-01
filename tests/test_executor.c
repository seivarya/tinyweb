#include <stdio.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <server/executor.h>

static void dummy_task(void *arg) {
	(void)arg;
}

static void test_wait_none(void) {
	executor *exec = exec_create(4);
	assert(exec != NULL);

	int res = exec_wait(exec);
	assert(res == 0);

	exec_destroy(exec);
	fprintf(stdout, "[%s]: debug passed test_wait_none\n", __func__);
}

static void test_add_stop(void) {
	executor *exec = exec_create(4);
	assert(exec != NULL);

	pthread_mutex_lock(&(exec->mutex));
	exec->stop = true;
	pthread_mutex_unlock(&(exec->mutex));

	bool added = exec_add_work(exec, dummy_task, NULL);
	assert(added == false);

	exec_destroy(exec);
	fprintf(stdout, "[%s]: debug passed test_add_stop\n", __func__);
}

int main(void) {
	fprintf(stdout, "[%s]: debug running executor tests\n", __func__);
	test_wait_none();
	test_add_stop();
	fprintf(stdout, "[%s]: debug all executor tests passed\n", __func__);
	return 0;
}
