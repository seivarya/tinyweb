/* slist_node.c: singly linked list node methods */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/slist/slist_node.h>

slist_node *slist_node_construct(void *data, size_t size) {
        if (!data) {
                fprintf(stderr, "[ERROR]: %s :: null data pointer\n", __func__);
                return NULL;
        }
        slist_node *node = malloc(sizeof(slist_node));
        if (!node) {
                fprintf(stderr, "[ERROR]: %s :: malloc failed for slist_node struct\n", __func__);
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

        return node;
}

void slist_node_destruct(slist_node *node) {
        if (!node) {
                fprintf(stderr, "[ERROR]: %s :: null node pointer\n", __func__);
                return;
        }

        if (node->data) {
                free(node->data);
                node->data = NULL;
        }

        free(node);
} /* slist_node_c */
