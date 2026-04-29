/* queue_node.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/queue/queue_node.h>

queue_node *queue_node_construct(void *data, size_t size) {
        queue_node *node = malloc(sizeof(queue_node));
        if (!node) {
                fprintf(stderr,
                        "error: [%s]: malloc failed for sizeof(queue_node)\n",
                        __func__);
                return NULL;
        }

        node->data = malloc(size);
        if (!node->data) {
                fprintf(stderr,
                        "error: [%s]: malloc failed for node->data\n",
                        __func__);
                free(node);
                return NULL;
        }

        memcpy(node->data, data, size);
        node->next = NULL;

        fprintf(stderr, "debug: [%s]: queue node constructed\n", __func__);
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
        fprintf(stderr, "debug: [%s]: queue node destructed\n", __func__);
}
