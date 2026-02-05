/* bnode.h: binary search tree node interface */

#ifndef BNODE_H 
#define BNODE_H 

#include <stdlib.h>

typedef struct bnode bnode;

struct bnode {
	void *data;
	bnode *next;
	bnode *prev;
};

bnode* bnode_construct(void *data, size_t size);
void bnode_destruct(bnode* node);

#endif /* bnode_h */
