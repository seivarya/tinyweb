#ifndef DICT_H
#define DICT_H

#define HASH_SIZE 69
#include <nodes/entry.h>

typedef struct dict {
	entry* entries[HASH_SIZE];
} dict;


dict* dict_construct(void);

char* dict_search(dict* dictionary, const char* key);
void dict_insert(dict* dictionary, const char* key, const char* value);
void dict_remove(dict* dictionary, const char* key);

unsigned int hash(const char *key);
#endif
