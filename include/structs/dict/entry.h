/* entry.h */

#ifndef ENTRY_H
#define ENTRY_H

#include <stddef.h>

typedef struct entry entry;

struct entry {
	char *key;
	void *value;
	entry *next;
};

entry *entry_construct(const char *key, const void *value, size_t size);
void entry_destruct(entry *entry_ptr);

#endif /* entry.h */
