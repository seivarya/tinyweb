/* entry.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/dict/entry.h>

entry *entry_construct(const char *key, const char *value) {
        entry *node = malloc(sizeof(entry));
        if (!node) {
                fprintf(stderr,
                        "error: [%s]: malloc failed for sizeof(entry)\n",
                        __func__);
                return NULL;
        }

        if (!key || !value) {
                fprintf(stderr, "error: [%s]: missing key or value\n",
                        __func__);
                free(node);
                return NULL;
        }

        node->key = malloc(strlen(key) + 1);
        strcpy(node->key, key);

        node->value = malloc(strlen(value) + 1);
        strcpy(node->value, value);

        node->next = NULL;

        fprintf(stderr, "debug: [%s]: entry constructed for key '%s'\n", __func__, key);
        return node;
}

void entry_destruct(entry *node) {
        if (!node) return;
        fprintf(stderr, "debug: [%s]: entry destructed for key '%s'\n", __func__, node->key);
        free(node->key);
        free(node->value);
        free(node);
}
