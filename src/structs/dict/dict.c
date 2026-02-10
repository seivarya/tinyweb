#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <structs/dict.h>
#include <nodes/entry.h>


static inline int _validate_dict_ptr(dict *dictionary) {
	if (dictionary == NULL) {
		fprintf(stderr, "Error: %s: Dictionary pointer is NULL.\n", __func__);
		return 0;
	}
	return 1;
}

static inline int _validate_key(const char *key) {
	if (key == NULL || *key == '\0') {
		fprintf(stderr, "Error: %s: Key is NULL or empty.\n", __func__);
		return 0;
	}
	return 1;
}

static inline void _validate_entry_construction(entry *node) {
	if (!node) {
		fprintf(stderr, "Error: %s: Failed to construct dictionary entry node, aborting.\n", __func__);
		exit(3);
	}
}

dict* dict_construct(void) {
	dict* dictionary = malloc(sizeof(struct dict));
	if (!dictionary) {
		fprintf(stderr, "=== error: dict_construct(): malloc failed ===\n");
		return NULL;
	}

	for (size_t i = 0; i < HASH_SIZE; i++) {
		dictionary->entries[i] = NULL;
	}
	return dictionary;
}

char* dict_search(dict* dictionary, const char* key) {
	if (!_validate_dict_ptr(dictionary) || !_validate_key(key))
		return NULL;

	unsigned int index = hash(key);
	entry* node = dictionary->entries[index];

	while (node != NULL) {
		if (strcmp(node->key, key) == 0) {
			return node->value;
		}
		node = node->next;
	}

	fprintf(stderr, "Error: %s: Key '%s' not found in dictionary.\n", __func__, key);
	return NULL;
}

void dict_insert(dict* dictionary, const char* key, const char* value) {
	if (!_validate_dict_ptr(dictionary) || !_validate_key(key)) {
		return;
	}
	if (value == NULL) {
		fprintf(stderr, "Error: %s: Value pointer is NULL for key '%s'.\n", __func__, key);
		return;
	}

	unsigned int index = hash(key);
	entry* node = entry_construct(key, value);
	_validate_entry_construction(node);

	/* insert at head of bucket chain */
	node->next = dictionary->entries[index];
	dictionary->entries[index] = node;
}

void dict_remove(dict* dictionary, const char* key) {
	if (!_validate_dict_ptr(dictionary) || !_validate_key(key))
		return;

	unsigned int index = hash(key);
	entry* node = dictionary->entries[index];
	entry* prev = NULL;

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

	fprintf(stderr, "Error: %s: Key '%s' not found in dictionary for removal.\n", __func__, key);
}

unsigned int hash(const char *key) {
	if (!_validate_key(key))
		return 0;

	unsigned long h = 5381;
	unsigned char c;
	while ((c = (unsigned char)*key++)) {
		h = ((h << 5) + h) + c;  /* h = h*33 + c */
	}
	return (unsigned int)(h % HASH_SIZE);
}
