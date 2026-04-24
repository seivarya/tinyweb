#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/tree/bst_node.h>

bst_node *bst_node_construct(void *data, size_t size) {
        bst_node *node = malloc(sizeof(bst_node));
        if (!node) {
                fprintf(stderr,
                        "[bst_node_construct]: malloc failed for "
                        "sizeof(bst_node)\n[%s]: %s\n",
                        __func__, __FILE__);
                return NULL;
        }

        node->data = malloc(size);
        if (!node->data) {
                fprintf(stderr,
                        "[bst_node_construct]: malloc failed for "
                        "node->data\n[%s]: %s\n",
                        __func__, __FILE__);
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
