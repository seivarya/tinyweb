#include "dictionary.h"

void insert_dict(struct dictionary *dict, void *key, int key_size, void *value, int value_size);
void * search_dict (struct dictionary *dict, void *key);

struct dictionary dict_constructor(int (*compare)(void *key_fir, void *key_sec)) {

	struct dictionary dict;

	dict.tree = binary_tree_constructor(compare); // passing the user defined compare function.
	dict.dict_insert = insert_dict;
	dict.dict_search = search_dict;

	return dict;
}

void dict_destructor(struct dictionary *dict) {
	free(dict->tree.head);
	free(&(dict->tree));
	printf("=== dictionary destroyed ===\n");
}

void insert_dict(struct dictionary *dict, void *key, int key_size, void *value, int value_size) {

	struct entry *entry = malloc(sizeof(struct entry));
	*entry = entry_constructor(key, key_size, value, value_size);

	dict->tree.binary_node_insert(&dict->tree, entry, sizeof(struct entry)); // dict ptr so -> & tree.insert will treat entry struct as the data
	printf("data inserted\n");
}

void * search_dict(struct dictionary *dict, void *key) {

	void *result = dict->tree.binary_node_search(&dict->tree, key);
	if (!result) {
		printf("=== invalid key ===\n");
		exit(1);
	} else {
		return ((struct entry *)result); // cast entry * and return.
	}
}
