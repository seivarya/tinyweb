#ifndef ENTRY_H
#define ENTRY_H

typedef struct entry entry;

struct entry {
	char* key;
	char* value; // void*
	entry *next;
};

entry* entry_construct(const char* key, const char* value);
void entry_destruct(entry *entry);

#endif /* entry_h */
