/* queue_node.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/queue/queue_node.h>

queue_node *queue_node_construct(void *data, size_t size) {
        if (!data) {
                fprintf(stdout, "[%s]: error invalid arguments queue_node.c\n", __func__);
                return NULL;
        }
        queue_node *node = malloc(sizeof(queue_node));
        if (!node) {
                fprintf(stdout, "[%s]: error malloc failed for sizeof(queue_node) queue_node.c\n", __func__);
                return NULL;
        }

        node->data = malloc(size);
        if (!node->data) {
                fprintf(stdout, "[%s]: error malloc failed for node->data queue_node.c\n", __func__);
                free(node);
                return NULL;
        }

        memcpy(node->data, data, size);
        node->next = NULL;

        fprintf(stdout, "[%s]: debug queue node constructed queue_node.c\n", __func__);
        return node;
}

void queue_node_destruct(queue_node *node) {
        if (!node) {
                fprintf(stdout, "[%s]: error invalid arguments queue_node.c\n", __func__);
                return;
        }

        if (node->data) {
                free(node->data);
                node->data = NULL;
        }

        free(node);
        fprintf(stdout, "[%s]: debug queue node destructed queue_node.c\n", __func__);
}
