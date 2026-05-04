/* bst.c: binary search tree methods */

#include <stdio.h>
#include <stdlib.h>

#include <structs/tree/bst.h>
#include <structs/tree/bst_node.h>

/* info: private methods (rvlib-style validation) */

static inline int _validate_bst_ptr(bst *tree) {
        if (tree == NULL) {
                fprintf(stderr, "[ERROR]: %s :: bst pointer is null\n", __func__);
                return 0;
        }
        if (tree->bst_cmpr == NULL) {
                fprintf(stderr, "[ERROR]: %s :: bst comparator function is null\n", __func__);
                return 0;
        }
        return 1;
}

static inline void _validate_bst_node_construction(bst *tree, bst_node *node) {
        (void)tree;
        if (!node) {
                fprintf(stderr, "[ERROR]: %s :: bst node construction failed, aborting\n", __func__);
                exit(3);
        }
}

static inline int _validate_bst_nonempty(bst *tree) {
        if (!_validate_bst_ptr(tree))
                return 0;
        if (tree->head == NULL) {
                fprintf(stderr, "[ERROR]: %s :: bst is empty\n", __func__);
                return 0;
        }
        return 1;
}

/* info: public methods */

bst *bst_construct(int (*cmpr_func)(void *a, void *b)) {
        bst *tree = malloc(sizeof(bst));
        if (!tree) {
                fprintf(stderr, "[ERROR]: %s :: malloc failed for bst struct\n", __func__);
                return NULL;
        }
        tree->head = NULL;
        tree->bst_cmpr = cmpr_func;
        return tree;
}

static void _bst_destroy_nodes(bst_node *node) {
        if (!node) return;
        _bst_destroy_nodes(node->prev);
        _bst_destroy_nodes(node->next);
        bst_node_destruct(node);
}

void bst_destruct(bst *tree) {
        if (!_validate_bst_ptr(tree))
                return;

        _bst_destroy_nodes(tree->head);
        free(tree);
}

bst_node *bst_iterate(bst *tree, bst_node *cursor, void *data, int *direction) {
        if (!_validate_bst_ptr(tree) || cursor == NULL || data == NULL ||
            direction == NULL) {
                fprintf(stderr, "[ERROR]: %s :: invalid arguments to bst_iterate\n", __func__);
                return NULL;
        }

        int iterfst = 0;
        if (iterfst == 0) {
                *direction = 1;
                iterfst++;
        }

        if (tree->bst_cmpr(cursor->data, data) == -1) {
                if (cursor->next) {
                        return bst_iterate(tree, cursor->next, data, direction);
                } else {
                        *direction = 1;
                        return cursor;
                }
        } else if (tree->bst_cmpr(cursor->data, data) == 1) {
                if (cursor->prev) {
                        return bst_iterate(tree, cursor->prev, data, direction);
                } else {
                        *direction = -1;
                        return cursor;
                }
        } else {
                *direction = 0;
                return cursor;
        }
}

void *bst_search(bst *tree, void *data) {
        if (!_validate_bst_nonempty(tree)) return NULL;
        if (data == NULL) {
                fprintf(stdout, "[%s]: error invalid arguments bst.c\n", __func__);
                return NULL;
        }

        if (tree->head->data == data) {
                return data;
        }

        int direction = 0;
        bst_node *cursor = bst_iterate(tree, tree->head, data, &direction);
        if (!cursor)
                return NULL;

        if (direction == 0) {
                return cursor->data;
        } else {
                fprintf(stderr, "[ERROR]: %s :: node not found in bst\n", __func__);
                return NULL;
        }
}

void bst_insert(bst *tree, void *data, size_t size) {
        if (!_validate_bst_ptr(tree)) return;
        if (data == NULL) {
                fprintf(stderr, "[ERROR]: %s :: null data pointer\n", __func__);
                return;
        }

        bst_node *node_to_insert = bst_node_construct(data, size);
        _validate_bst_node_construction(tree, node_to_insert);

        if (tree->head == NULL) {
                tree->head = node_to_insert;
                return;
        }

        int direction = 1;
        bst_node *cursor = bst_iterate(tree, tree->head, data, &direction);
        if (!cursor)
                return;

        if (direction == 1) {
                cursor->next = node_to_insert;
        } else if (direction == -1) {
                cursor->prev = node_to_insert;
        } else {
                fprintf(stderr, "[ERROR]: %s :: duplicate node, already exists in bst\n", __func__);
                return;
        }
}
