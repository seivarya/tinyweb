/* queue_node.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/queue/queue_node.h>

queue_node *queue_node_construct(void *data, size_t size) {
        if (!data) {
                fprintf(stderr, "[ERROR]: %s :: null data pointer\n", __func__);
                return NULL;
        }
        queue_node *node = malloc(sizeof(queue_node));
        if (!node) {
                fprintf(stderr, "[ERROR]: %s :: malloc failed for queue_node struct\n", __func__);
                return NULL;
        }

        node->data = malloc(size);
        if (!node->data) {
                fprintf(stderr, "[ERROR]: %s :: malloc failed for node data\n", __func__);
                free(node);
                return NULL;
        }

        memcpy(node->data, data, size);
        node->next = NULL;

        fprintf(stdout, "[DEBUG]: %s :: queue node constructed\n", __func__);
        return node;
}

void queue_node_destruct(queue_node *node) {
        if (!node) {
                fprintf(stderr, "[ERROR]: %s :: null node pointer\n", __func__);
                return;
        }

        if (node->data) {
                free(node->data);
                node->data = NULL;
        }

        free(node);
        fprintf(stdout, "[DEBUG]: %s :: queue node destructed\n", __func__);
}                
