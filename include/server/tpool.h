#ifndef TPOOL_H
#define TPOOL_H

#include <stdbool.h>
#include <stddef.h>
#include <pthread.h>

#include <structs/queue.h>
#include <server/server.h>

typedef struct thread_pool {
	bool shutdown;
} thread_pool;

#endif
