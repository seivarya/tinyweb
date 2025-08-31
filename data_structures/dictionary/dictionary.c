#include "dictionary.h"

void insert (struct dictionary *dict, void *key, int key_size, void *value, int value_size);
void * search (struct dictionary *dict, void *key);

struct dictionary dict_constructor(int (*compare)(void *key_fir, void *key_sec)) {

	struct dictionary dict;

	dict.tree = binary_tree_constructor(compare); // passing the user defined compare function.
	dict.insert = insert;
	dict.search = search;

	return dict;
}

void insert(struct dictionary *dict, void *key, int key_size, void *value, int value_size) {
	struct entry entry = entry_constructor(key, key_size, value, value_size);

	dict->tree.insert(&dict->tree, &entry, sizeof(entry)); // dict ptr so -> & tree.insert will treat entry struct as the data
}

void * search(struct dictionary *dict, void *key) {
	void * result = dict->tree.search(&dict->tree, key);

	if (result) {
		return ((struct entry *)result)->value; // cast entry * and return the val.
	} else {
		printf("=== invalid key ===");
		exit(1);
	}
}
