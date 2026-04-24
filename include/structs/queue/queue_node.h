#include <stdlib.h>

#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H
typedef struct queue_node queue_node;

struct queue_node {
        void *data;
        queue_node *next;
};

queue_node *queue_node_construct(void *data, size_t size);
void queue_node_destruct(queue_node *node);

#endif /* queue_node_h */
