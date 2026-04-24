#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/queue/queue_node.h>

queue_node *queue_node_construct(void *data, size_t size) {
        queue_node *node = malloc(sizeof(queue_node));
        if (!node) {
                fprintf(stderr,
                        "[queue_node_construct]: malloc failed for "
                        "sizeof(queue_node)\n[%s]: %s\n",
                        __func__, __FILE__);
                return NULL;
        }

        node->data = malloc(size);
        if (!node->data) {
                fprintf(stderr,
                        "[queue_node_construct]: malloc failed for "
                        "node->data\n[%s]: %s\n",
                        __func__, __FILE__);
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
