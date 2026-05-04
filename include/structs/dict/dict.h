/* dict.h */

#ifndef DICT_H
#define DICT_H

#include <structs/dict/entry.h>
#include <stddef.h>

#define HASH_SIZE 69

typedef struct dict {
	entry *entries[HASH_SIZE];
} dict;

dict *dict_construct(void);
void dict_destruct(dict *dictionary);

void *dict_search(dict *dictionary, const char *key);
void dict_insert(dict *dictionary, const char *key, const void *value, size_t size);
void dict_remove(dict *dictionary, const char *key);

unsigned int hash(const char *key);

#endif /* dict.h */
