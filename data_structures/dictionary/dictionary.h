#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../tree/binary_tree.h"
#include "entry/entry.h"

struct dictionary {
	struct binary_tree tree;
	void (*insert)(struct dictionary *dict, void *key, int key_size, void *value, int value_size);
	void * (*search)(struct dictionary *dict, void *key);
	
};

struct dictionary dict_constructor(int (*compare)(void *key_fir, void *key_sec));
void dict_destructor(struct dictionary *dict);

#endif /* DICTIONARY_H */
