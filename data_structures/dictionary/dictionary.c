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

void insert_dict(struct dictionary *dict, void *key, int key_size, void *value, int value_size) {
	struct entry entry = entry_constructor(key, key_size, value, value_size);

	dict->tree.binary_node_insert(&dict->tree, &entry, sizeof(struct entry)); // dict ptr so -> & tree.insert will treat entry struct as the data
}

void * search_dict(struct dictionary *dict, void *key) {

	printf("here");
	void * result = dict->tree.binary_node_search(&dict->tree, key);
	if (result) {
		return ((struct entry *)result)->value; // cast entry * and return the val.
	} else {
		printf("=== invalid key ===");
		exit(1);
	}
}
