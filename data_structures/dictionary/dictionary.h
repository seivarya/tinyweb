#include <stdio.h>


struct dict {
	void *key;
	void *value;
};

struct dict dict_constructor(void *key, void *value);

