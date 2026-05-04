/* entry.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/dict/entry.h>

entry *entry_construct(const char *key, const void *value, size_t size) {
        entry *node = malloc(sizeof(entry));
        if (!node) {
                fprintf(stderr, "[ERROR]: %s :: malloc failed for entry struct\n", __func__);
                return NULL;
        }

        if (!key || !value) {
                fprintf(stderr, "[ERROR]: %s :: missing key or value\n", __func__);
                free(node);
                return NULL;
        }

        node->key = malloc(strlen(key) + 1);
        strcpy(node->key, key);

        node->value = malloc(size);
        if (!node->value) {
                fprintf(stderr, "[ERROR]: %s :: malloc failed for entry value\n", __func__);
                free(node->key);
                free(node);
                return NULL;
        }
        memcpy(node->value, value, size);

        node->next = NULL;

        fprintf(stdout, "[DEBUG]: %s :: entry constructed for key '%s'\n", __func__, key);
        return node;
}

void entry_destruct(entry *node) {
        if (!node) {
                fprintf(stderr, "[ERROR]: %s :: null entry pointer\n", __func__);
                return;
        }
        fprintf(stdout, "[DEBUG]: %s :: entry destructed for key '%s'\n", __func__, node->key);
        free(node->key);
        free(node->value);
        free(node);
}
