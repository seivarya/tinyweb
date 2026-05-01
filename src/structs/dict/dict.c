/* dict.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <structs/dict/dict.h>
#include <structs/dict/entry.h>

static inline int _validate_dict_ptr(dict *dictionary) {
        if (dictionary == NULL) {
                fprintf(stdout, "[%s]: error dictionary pointer is null dict.c\n", __func__);
                return 0;
        }
        return 1;
}

static inline int _validate_key(const char *key) {
        if (key == NULL || *key == '\0') {
                fprintf(stdout, "[%s]: error key is null or empty dict.c\n", __func__);
                return 0;
        }
        return 1;
}

static inline void _validate_entry_construction(entry *node) {
        if (!node) {
                fprintf(stdout, "[%s]: error failed to construct dictionary entry node aborting dict.c\n", __func__);
                exit(3);
        }
}

dict *dict_construct(void) {
        dict *dictionary = malloc(sizeof(struct dict));
        if (!dictionary) {
                fprintf(stdout, "[%s]: error malloc failed dict.c\n", __func__);
                return NULL;
        }

        for (size_t i = 0; i < HASH_SIZE; i++) {
                dictionary->entries[i] = NULL;
        }
        fprintf(stdout, "[%s]: debug dictionary constructed dict.c\n", __func__);
        return dictionary;
}

void dict_destruct(dict *dictionary) {
        if (!_validate_dict_ptr(dictionary))
                return;

        for (size_t i = 0; i < HASH_SIZE; i++) {
                entry *node = dictionary->entries[i];
                while (node != NULL) {
                        entry *next = node->next;
                        entry_destruct(node);
                        node = next;
                }
        }
        free(dictionary);
        fprintf(stdout, "[%s]: debug dictionary destructed dict.c\n", __func__);
}

void *dict_search(dict *dictionary, const char *key) {
        if (!_validate_dict_ptr(dictionary) || !_validate_key(key))
                return NULL;

        unsigned int index = hash(key);
        entry *node = dictionary->entries[index];

        while (node != NULL) {
                if (strcmp(node->key, key) == 0) {
                        return node->value;
                }
                node = node->next;
        }

        fprintf(stdout, "[%s]: error key '%s' not found in dictionary dict.c\n", __func__, key);
        return NULL;
}

void dict_insert(dict *dictionary, const char *key, const void *value, size_t size) {
        if (!_validate_dict_ptr(dictionary) || !_validate_key(key)) {
                return;
        }
        if (value == NULL) {
                fprintf(stdout, "[%s]: error value pointer is null for key '%s' dict.c\n", __func__, key);
                return;
        }

        unsigned int index = hash(key);
        entry *node = entry_construct(key, value, size);
        _validate_entry_construction(node);

        /* insert at head of bucket chain */
        node->next = dictionary->entries[index];
        dictionary->entries[index] = node;
}

void dict_remove(dict *dictionary, const char *key) {
        if (!_validate_dict_ptr(dictionary) || !_validate_key(key))
                return;

        unsigned int index = hash(key);
        entry *node = dictionary->entries[index];
        entry *prev = NULL;

        while (node != NULL) {
                if (strcmp(node->key, key) == 0) {
                        if (prev == NULL) {
                                dictionary->entries[index] = node->next;
                        } else {
                                prev->next = node->next;
                        }
                        entry_destruct(node);
                        return;
                }
                prev = node;
                node = node->next;
        }

        fprintf(stdout, "[%s]: error key '%s' not found in dictionary for removal dict.c\n", __func__, key);
}

unsigned int hash(const char *key) {
        if (!_validate_key(key))
                return 0;

        unsigned long h = 5381;
        unsigned char c;
        while ((c = (unsigned char)*key++)) {
                h = ((h << 5) + h) + c; /* h = h*33 + c */
        }
        return (unsigned int)(h % HASH_SIZE);
}
