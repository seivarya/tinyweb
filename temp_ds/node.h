#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum d_types {
	Special,
	Int,
	Float,
	Char,
	Double,
	Long,
	Bool
};

struct node {
	void *data;
	int data_type;
	int size;
	struct node *next;
};

struct node node_constructor(void *data, int data_type, int size);
void node_destructor(struct node *node);

#endif
