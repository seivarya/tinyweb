#include "../dictionary/dictionary.h"
#include <stdio.h>
#include <string.h>

void print_dict(struct node *node);

// utility: print dictionary in-order
void print_dict(struct node *node) {
	if (!node) return;
	print_dict(node->previous);

	struct entry *entry = (struct entry *)node->data;
	printf("{ \"%s\": \"%s\" }\n", (char *)entry->key, (char *)entry->value);

	print_dict(node->next);
}

int main(void) {
	printf("=== dictionary test ===\n");

	// construct dictionary using string-key comparator
	struct dictionary dict = dict_constructor(compare_string_keys);

	// test case 1: insertion
	printf("\n=== inserting entries ===\n");
	const char *keys[]   = { "apple", "banana", "pear", "orange", "kiwi" };
	const char *values[] = { "red",   "yellow", "green", "orange", "green" };

	for (int i = 0; i < 5; i++) {
		dict.dict_insert(&dict,
		   (void *)keys[i], strlen(keys[i]) + 1,
		   (void *)values[i], strlen(values[i]) + 1);
		printf("=== inserted: { \"%s\": \"%s\" } ===\n", keys[i], values[i]);
	}

	// test case 2: print order
	printf("\n=== printing dictionary (sorted order) ===\n");
	print_dict(dict.tree.head);

	// test case 3: search existing keys
	printf("\n=== searching existing keys ===\n");
	const char *search_keys[] = { "banana", "kiwi", "apple" };
	for (int i = 0; i < 3; i++) {
		struct entry *found = dict.dict_search(&dict, (void *)search_keys[i]);
		printf("=== search \"%s\" -> value: \"%s\" ===\n",
	 search_keys[i], (char *)found->value);
	}

	// test case 4: search missing key
	printf("\n=== searching missing key ===\n");
	const char *missing_key = "grape";
	printf("=== search \"%s\" ===\n", missing_key);
	struct entry *missing = dict.dict_search(&dict, (void *)missing_key);
	if (!missing) {
		printf("=== key \"%s\" not found (pass) ===\n", missing_key);
	} else {
		printf("=== error: unexpected value for \"%s\" ===\n", missing_key);
	}

	// test case 5: duplicate insert
	printf("\n=== inserting duplicate key (banana) with new value ===\n");
	const char *new_value = "brown";
	dict.dict_insert(&dict,
		  (void *)"banana", strlen("banana") + 1,
		  (void *)new_value, strlen(new_value) + 1);

	printf("=== dictionary after duplicate insert ===\n");
	print_dict(dict.tree.head);

	// cleanup
	printf("\n=== dictionary test completed ===\n");
	// normally free all nodes/entries here, os will reclaim memory on exit
	return 0;
}
