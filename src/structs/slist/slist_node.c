/* slist_node.c: singly linked list node methods */

#include <stdio.h>
#include <string.h>

#include <nodes/slist_node.h>

slist_node *slist_node_construct(void *data, size_t size) {
  slist_node *node = malloc(sizeof(slist_node));
  if (!node) {
    perror("=== malloc failed: slist_node_construct(): sizeof(slist_node) ===");
    return NULL;
  }

  node->data = malloc(size);
  if (!node->data) {
    perror("=== malloc failed: slist_node_construct(): node->data ===");
    free(node);
    return NULL;
  }

  memcpy(node->data, data, size);
  node->next = NULL;

  return node;
}

void slist_node_destruct(slist_node *node) {
  if (!node)
    return;

  if (node->data) {
    free(node->data);
    node->data = NULL;
  }

  free(node);
} /* slist_node_c */
