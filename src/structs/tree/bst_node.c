#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/tree/bst_node.h>

bst_node *bst_node_construct(void *data, size_t size) {
        if (!data) {
                fprintf(stderr, "[ERROR]: %s :: null data pointer\n", __func__);
                return NULL;
        }
        bst_node *node = malloc(sizeof(bst_node));
        if (!node) {
                fprintf(stderr, "[ERROR]: %s :: malloc failed for bst_node struct\n", __func__);
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
        node->prev = NULL;

        return node;
}

void bst_node_destruct(bst_node *node) {
        if (!node) {
                fprintf(stderr, "[ERROR]: %s :: null node pointer\n", __func__);
                return;
        }
        if (node->data) {
                free(node->data);
                node->data = NULL;
        }

        free(node);
} /* bst_node_c */
