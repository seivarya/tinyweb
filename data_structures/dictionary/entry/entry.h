#include <stdlib.h>

struct entry {
	void *key;
	void *value;
};

struct entry entry_constructor(void *key, int key_size, void *value, int value_size);
void entry_destructor(struct entry *entry); /* ENTRY_H */
