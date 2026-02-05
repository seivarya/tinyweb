// entry.h > definition of struct entry and it's methods

#ifndef ENTRY_H
#define ENTRY_H

//  INFO: entry object initialization

struct entry {
	void *key;
	void *value;
};

//  INFO: methods

struct entry entry_constructor(void *key, int key_size, void *value, int value_size);
void entry_destructor(struct entry *entry);

#endif /* ENTRY_H */
