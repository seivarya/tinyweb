#include <stdio.h>
#include <string.h>

#include <nodes/queue_node.h>

queue_node *queue_node_construct(void *data, size_t size) {
  queue_node *node = malloc(sizeof(queue_node));
  if (!node) {
    perror("=== malloc failed: queue_node_construct(): sizeof(queue_node) ===");
    return NULL;
  }

  node->data = malloc(size);
  if (!node->data) {
    perror("=== malloc failed: queue_node_construct(): node->data ===");
    free(node);
    return NULL;
  }

  memcpy(node->data, data, size);
  node->next = NULL;

  return node;
}

void queue_node_destruct(queue_node *node) {
  if (!node)
    return;

  if (node->data) {
    free(node->data);
    node->data = NULL;
  }

  free(node);
} /* queue_node_c */
