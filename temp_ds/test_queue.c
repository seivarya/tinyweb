#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//FIX: pop and peek return node instead of data. so this test is mostly incorrect. fix the pop peak returned node and point it to that specific node's data instead.


int main(void) {
	struct queue q = queue_constructor();

	printf("==== pushing ints ====\n");
	for (int i = 0; i < 5; i++) {
		int *value = malloc(sizeof(int));
		*value = i * 10;
		q.push(&q, value, Int);

		// peek after each push
		struct node *peeked = q.peek(&q);
		printf("peek after push %d: %d\n", i, *(int *)peeked->data);
	}

	printf("==== pushing float ====\n");
	float *fval = malloc(sizeof(float));
	*fval = 3.14f;
	q.push(&q, fval, Float);
	struct node *peeked1 = q.peek(&q);
	printf("peek after pushing float (still head int 0): %d\n", *(int *)peeked1->data);

	printf("==== pushing double ====\n");
	double *dval = malloc(sizeof(double));
	*dval = 2.71828;
	q.push(&q, dval, Double);
	struct node *peeked2 = q.peek(&q);
	printf("peek after pushing double (still head int 0): %d\n", *(int *)peeked2->data);

	printf("==== pushing char ====\n");
	char *cval = malloc(sizeof(char));
	*cval = 'Z';
	q.push(&q, cval, Char);

	printf("==== pushing long ====\n");
	long *lval = malloc(sizeof(long));
	*lval = 123456789L;
	q.push(&q, lval, Long);

	printf("==== pushing bool ====\n");
	bool *bval = malloc(sizeof(bool));
	*bval = true;
	q.push(&q, bval, Bool);

	printf("\n==== popping everything (with peek before pop) ====\n");
	while (q.list.length > 0) {
		struct node *peeked = q.peek(&q);
		printf("peek sees next to pop -> ");
		switch (peeked->data_type) {
			case Int:    printf("Int: %d\n", *(int *)peeked->data); break;
			case Float:  printf("Float: %f\n", *(float *)peeked->data); break;
			case Double: printf("Double: %lf\n", *(double *)peeked->data); break;
			case Char:   printf("Char: %c\n", *(char *)peeked->data); break;
			case Long:   printf("Long: %ld\n", *(long *)peeked->data); break;
			case Bool:   printf("Bool: %s\n", *(bool *)peeked->data ? "true" : "false"); break;
		}

		struct node *node = q.pop(&q);
		printf("popped same -> ");
		switch (node->data_type) {
			case Int:    printf("Int: %d\n", *(int *)node->data); break;
			case Float:  printf("Float: %f\n", *(float *)node->data); break;
			case Double: printf("Double: %lf\n", *(double *)node->data); break;
			case Char:   printf("Char: %c\n", *(char *)node->data); break;
			case Long:   printf("Long: %ld\n", *(long *)node->data); break;
			case Bool:   printf("Bool: %s\n", *(bool *)node->data ? "true" : "false"); break;
		}
		printf("---\n");

		node_destructor(node); // cleanup
	}

	printf("\nall queue tests passed.\n");
	return 0;
}
