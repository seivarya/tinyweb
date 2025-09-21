#include <stdlib.h>

//  INFO: entry object initialization

struct entry {
	void *key;
	void *value;
};

//  INFO: methods
struct entry entry_constructor(void *key, int key_size, void *value, int value_size);
void entry_destructor(struct entry *entry); /* ENTRY_H */
