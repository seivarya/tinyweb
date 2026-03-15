#include <stdio.h>
#include <string.h>

#include <nodes/bst_node.h>

bst_node *bst_node_construct(void *data, size_t size) {
  bst_node *node = malloc(sizeof(bst_node));
  if (!node) {
    perror("=== malloc failed: bst_node_construct(): sizeof(bst_node) ===");
    return NULL;
  }

  node->data = malloc(size);
  if (!node->data) {
    perror("=== malloc failed: bst_node_construct(): node->data ===");
    free(node);
    return NULL;
  }
  memcpy(node->data, data, size);
  node->next = NULL;
  node->prev = NULL;

  return node;
}

void bst_node_destruct(bst_node *node) {
  if (!node)
    return;
  if (node->data) {
    free(node->data);
    node->data = NULL;
  }

  free(node);
} /* bst_node_c */
