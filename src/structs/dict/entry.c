#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nodes/entry.h>

entry* entry_construct(const char* key, const char* value) {
	entry* node = malloc(sizeof(entry));
	if (!node) {
		perror("=== malloc failed: entry_construct(): sizeof(stnode) ===");
		free(node);
		return NULL;
	}

	if (!key || !value) {
		perror("Error: missing?\n");
		return NULL;
	}

	node->key = malloc(strlen(key) + 1);
	strcpy(node->key, key);

	node->value = malloc(strlen(value) + 1);
	strcpy(node->value, value);

	node->next = NULL;

	return node;
}

void entry_destruct(entry *entry) {
	free(entry->key);
	free(entry->value);
	free(entry);
}
