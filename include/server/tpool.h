#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>

#include <server/server.h>
#include <structs/queue/queue.h>

#ifndef TPOOL_H
#define TPOOL_H
typedef struct thread_pool {
        bool shutdown;
} thread_pool;

#endif
