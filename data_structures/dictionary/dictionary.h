#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../tree/binary_tree.h"
#include "entry/entry.h"

//  INFO: dictionary  object initialization

struct dictionary {
	struct binary_tree tree;
	void (*dict_insert)(struct dictionary *dict, void *key, int key_size, void *value, int value_size);
	void * (*dict_search)(struct dictionary *dict, void *key);
	
};

//  INFO: methods
int compare_string_keys(void *entry_fir, void *entry_sec);
struct dictionary dict_constructor(int (*compare)(void *key_fir, void *key_sec));
void dict_destructor(struct dictionary *dict);

#endif /* DICTIONARY_H */
