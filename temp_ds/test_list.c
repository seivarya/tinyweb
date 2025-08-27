#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
	struct linked_list list = linked_list_constructor();

	// ==== Int ====
	int *ival = malloc(sizeof(int));
	*ival = 42;
	list.insert(&list, 0, ival, Int);
	struct node *ival_node = list.retrieve(&list, 0);
	printf("Int test: %d\n", *(int*)ival_node->data);

	// ==== Float ====
	float *fval = malloc(sizeof(float));
	*fval = 3.14f;
	list.insert(&list, 1, fval, Float);
	struct node *fval_node = list.retrieve(&list, 1);
	printf("Float test: %f\n", *(float*)fval_node->data);

	// ==== Double ====
	double *dval = malloc(sizeof(double));
	*dval = 2.718281828;
	list.insert(&list, 2, dval, Double);
	struct node *dval_node = list.retrieve(&list, 2);
	printf("Double test: %lf\n", *(double*)dval_node->data);

	// ==== Char ====
	char *cval = malloc(sizeof(char));
	*cval = 'X';
	list.insert(&list, 3, cval, Char);
	struct node *cval_node = list.retrieve(&list, 3);
	printf("Char test: %c\n", *(char*)cval_node->data);

	// ==== Long ====
	long *lval = malloc(sizeof(long));
	*lval = 123456789L;
	list.insert(&list, 4, lval, Long);
	struct node *lval_node = list.retrieve(&list, 4);
	printf("Long test: %ld\n", *(long*)lval_node->data);

	// ==== Bool ====
	bool *bval = malloc(sizeof(bool));
	*bval = true;
	list.insert(&list, 5, bval, Bool);
	struct node *bval_node = list.retrieve(&list, 5);
	printf("Bool test: %s\n", *(bool*)bval_node->data ? "true" : "false");

	// ==== Invalid Data Type ====
	printf("Now testing invalid data type (should exit with error):\n");
	char *ival2 = malloc(sizeof(char));
	*ival2 = 'x';
	// This should hit the "invalid data type" in get_size_for_d_type()
	list.insert(&list, 6, ival2, 9999);

	// Cleanup (won’t reach here if invalid test exits program)
	while (list.length > 0) {
		list.remove(&list, 0);
	}

	return 0;
}
