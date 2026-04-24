/* slist_node.c: singly linked list node methods */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/slist/slist_node.h>

slist_node *slist_node_construct(void *data, size_t size) {
        slist_node *node = malloc(sizeof(slist_node));
        if (!node) {
                fprintf(stderr,
                        "[slist_node_construct]: malloc failed for "
                        "sizeof(slist_node)\n[%s]: %s\n",
                        __func__, __FILE__);
                return NULL;
        }

        node->data = malloc(size);
        if (!node->data) {
                fprintf(stderr,
                        "[slist_node_construct]: malloc failed for "
                        "node->data\n[%s]: %s\n",
                        __func__, __FILE__);
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
