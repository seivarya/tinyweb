#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/dict/entry.h>

entry *entry_construct(const char *key, const char *value) {
        entry *node = malloc(sizeof(entry));
        if (!node) {
                fprintf(stderr,
                        "[entry_construct]: malloc failed for "
                        "sizeof(stnode)\n[%s]: %s\n",
                        __func__, __FILE__);
                free(node);
                return NULL;
        }

        if (!key || !value) {
                fprintf(stderr, "[entry_construct]: missing?\n[%s]: %s\n",
                        __func__, __FILE__);
                return NULL;
        }

        node->key = malloc(strlen(key) + 1);
        strcpy(node->key, key);

        node->value = malloc(strlen(value) + 1);
        strcpy(node->value, value);

        node->next = NULL;

        return node;
}

void entry_destruct(entry *node) {
        free(node->key);
        free(node->value);
        free(node);
}
