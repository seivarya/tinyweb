#include "dictionary.h"
#include <stdio.h>
#include <string.h>

//  INFO: function prototypes

void insert_dict(struct dictionary *dict, void *key, int key_size, void *value, int value_size);
void * search_dict (struct dictionary *dict, void *key);

//  INFO: dictionary constructor

struct dictionary dict_constructor(int (*compare)(void *key_fir, void *key_sec)) {

	struct dictionary dict;
	
	dict.tree = binary_tree_constructor(compare); // passing the user defined compare function.
	dict.dict_insert = insert_dict;
	dict.dict_search = search_dict;

	return dict;
}

//  INFO: dictionary destructor

void dict_destructor(struct dictionary *dict) {
	free(dict->tree.head);
	free(&(dict->tree));
}

//  INFO: public methods: line{14}

void insert_dict(struct dictionary *dict, void *key, int key_size, void *value, int value_size) {
	struct entry *entry = malloc(sizeof(struct entry));
	*entry = entry_constructor(key, key_size, value, value_size);

	dict->tree.binary_node_insert(&dict->tree, entry, sizeof(struct entry)); // dict ptr so -> & tree.insert will treat entry struct as the data
}

void * search_dict(struct dictionary *dict, void *key) {

	struct entry fake_entry = { .key = key };

	void *result = dict->tree.binary_node_search(&dict->tree, &fake_entry);
	if (!result) {
		printf("=== invalid key ===\n");
		exit(1);
	} else {
		return ((struct entry *)result); // cast entry * and return.
	}
}

//  INFO: string keys compare method

int compare_string_keys(void *entry_fir, void *entry_sec) {

	if (strcmp((char *)((struct entry *)entry_fir)->key,
	    (char *)((struct entry *)entry_sec)->key) > 0) {
		return 1;

	} else if (strcmp((char *)((struct entry *)entry_fir)->key,
		   (char *)((struct entry *)entry_sec)->key) < 0) {
		return -1;

	} else {
		return 0;
	}
}
