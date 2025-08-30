#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

struct dict dict_constructor(void *key, int key_size, void *value, int value_size) {
	struct dict dict;
	dict.key = malloc(key_size);
	dict.value = malloc(value_size);
} //  FIX: dict or entry?
