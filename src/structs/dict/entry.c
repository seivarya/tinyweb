/* entry.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/dict/entry.h>

entry *entry_construct(const char *key, const void *value, size_t size) {
        entry *node = malloc(sizeof(entry));
        if (!node) {
                fprintf(stdout, "[%s]: error malloc failed for sizeof(entry) entry.c\n", __func__);
                return NULL;
        }

        if (!key || !value) {
                fprintf(stdout, "[%s]: error missing key or value entry.c\n", __func__);
                free(node);
                return NULL;
        }

        node->key = malloc(strlen(key) + 1);
        strcpy(node->key, key);

        node->value = malloc(size);
        if (!node->value) {
                fprintf(stdout, "[%s]: error malloc failed for node->value entry.c\n", __func__);
                free(node->key);
                free(node);
                return NULL;
        }
        memcpy(node->value, value, size);

        node->next = NULL;

        fprintf(stdout, "[%s]: debug entry constructed for key '%s' entry.c\n", __func__, key);
        return node;
}

void entry_destruct(entry *node) {
        if (!node) {
                fprintf(stdout, "[%s]: error invalid arguments entry.c\n", __func__);
                return;
        }
        fprintf(stdout, "[%s]: debug entry destructed for key '%s' entry.c\n", __func__, node->key);
        free(node->key);
        free(node->value);
        free(node);
}
