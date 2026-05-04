/* queue.c */

#include <stdio.h>
#include <stdlib.h>

#include <structs/queue/queue.h>
#include <structs/queue/queue_node.h>

/* private methods */

static inline int _validate_queue_ptr(queue *q) {
        if (q == NULL) {
                fprintf(stderr, "[ERROR]: %s :: queue pointer is null\n", __func__);
                return 0;
        }
        return 1;
}

static inline void _validate_queue_node_construction(queue *q,
                                                     queue_node *node) {
        if (!node) {
                /* if node allocation failed, clean up the queue and abort */
                fprintf(stderr, "[ERROR]: %s :: queue node construction failed, aborting\n", __func__);
                queue_destruct(q);
                exit(3);
        }
}

/* public methods */

queue *queue_construct(void) {
        queue *q = malloc(sizeof(queue));
        if (q) {
                q->head = NULL;
                q->tail = NULL;
                q->length = 0;
                fprintf(stdout, "[DEBUG]: %s :: queue constructed\n", __func__);
                return q;
        }

        fprintf(stderr, "[ERROR]: %s :: malloc failed for queue struct\n", __func__);
        return NULL;
}

void queue_destruct(queue *q) {
        if (!_validate_queue_ptr(q))
                return;

        /* destroy all nodes */
        queue_node *current = q->head;
        while (current != NULL) {
                queue_node *next = current->next;
                queue_node_destruct(current);
                current = next;
        }

        free(q);
        fprintf(stdout, "[DEBUG]: %s :: queue destructed\n", __func__);
}

void enqueue(queue *q, void *data, size_t size) {
        if (!_validate_queue_ptr(q))
                return;
        if (!data) {
                fprintf(stderr, "[ERROR]: %s :: null data pointer\n", __func__);
                return;
        }

        queue_node *new_node = queue_node_construct(data, size);
        _validate_queue_node_construction(q, new_node);

        /* attach node to tail */
        if (q->length == 0) {
                q->head = new_node;
                q->tail = new_node;
        } else {
                q->tail->next = new_node;
                q->tail = new_node;
        }

        q->length++;
}

void dequeue(queue *q) {
        if (!_validate_queue_ptr(q))
                return;
        if (q->length == 0) {
                fprintf(stderr, "[ERROR]: %s :: attempted dequeue on empty queue\n", __func__);
                return;
        }

        queue_node *target = q->head;

        if (q->length == 1) {
                q->head = NULL;
                q->tail = NULL;
        } else {
                q->head = target->next;
        }

        queue_node_destruct(target);
        q->length--;
}

int is_qempty(queue *q) {
        if (!_validate_queue_ptr(q))
                return 1;

        return (q->length == 0);
}

void *get_front(queue *q) {
        if (!_validate_queue_ptr(q))
                return NULL;
        if (q->length == 0) {
                fprintf(stderr, "[ERROR]: %s :: attempted get_front on empty queue\n", __func__);
                return NULL;
        }

        return q->head;
}

void *get_rear(queue *q) {
        if (!_validate_queue_ptr(q))
                return NULL;
        if (q->length == 0) {
                fprintf(stderr, "[ERROR]: %s :: attempted get_rear on empty queue\n", __func__);
                return NULL;
        }

        return q->tail;
}
