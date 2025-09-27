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

void * search_dict(struct dictionary *dict, void *key) { //  FIX: user is giving us key so we've to make a fake entry out of it first in order to make it work
	
	struct entry entry = { 0 };
	entry.key = key; //  INFO: inserting key in fake entry

	void *result = dict->tree.binary_node_search(&dict->tree, &entry); //  FIX: we can't pass a fucking key this shit was causing segfault since yesterday. we've to pass struct entry type since the dictionary built on node wrapped on entry structure.

	if (!result) {
		printf("=== invalid key ===\n");
		return NULL;
	} else {
		return  (struct entry *)(result); // cast entry * and return.
	}
}

//  INFO: generic compare method

int compare_string_keys(void *entry_fir, void *entry_sec) {
	int result = strcmp(((struct entry *)entry_fir)->key,
		     ((struct entry *)entry_sec)->key);

	if (result > 0) {
		return 1;
	} else if (result < 0) {
		return -1;
	} else {
		return 0;
	}
}
