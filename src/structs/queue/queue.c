#include <stdio.h>
#include <stdlib.h>

#include <nodes/queue_node.h>
#include <structs/queue.h>

/* info: private methods (rvlib-style validation) */

static inline int _validate_queue_ptr(queue *q) {
  if (q == NULL) {
    fprintf(stderr, "Error: %s: Queue pointer is NULL.\n", __func__);
    return 0;
  }
  return 1;
}

static inline void _validate_queue_node_construction(queue *q,
                                                     queue_node *node) {
  if (!node) {
    /* if node allocation failed, clean up the queue and abort */
    queue_destruct(q);
    exit(3);
  }
}

static inline int _validate_qindex(queue *q, size_t index) {
  if (q == NULL) {
    fprintf(stderr, "Error: %s: Queue pointer is NULL for index validation.\n",
            __func__);
    return 0;
  }
  if (index >= q->length) {
    fprintf(stderr,
            "Error: %s: Index %zu out of bounds for queue length %zu.\n",
            __func__, index, q->length);
    return 0;
  }
  return 1;
}

/* info: public methods */

queue *queue_construct(void) {
  queue *q = malloc(sizeof(queue));
  if (q) {
    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
    return q;
  }

  fprintf(stderr, "=== error: queue_construct(): malloc failed ===\n");
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
}

void enqueue(queue *q, void *data, size_t size) {
  if (!_validate_queue_ptr(q))
    return;

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
    fprintf(stderr, "Error: %s: Attempted to dequeue from an empty queue.\n",
            __func__);
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
    fprintf(stderr, "Error: %s: Attempted to get front from an empty queue.\n",
            __func__);
    return NULL;
  }

  return q->head;
}

void *get_rear(queue *q) {
  if (!_validate_queue_ptr(q))
    return NULL;
  if (q->length == 0) {
    fprintf(stderr, "Error: %s: Attempted to get rear from an empty queue.\n",
            __func__);
    return NULL;
  }

  return q->tail;
} /* queue_c */
