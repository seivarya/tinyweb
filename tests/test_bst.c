#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <structs/tree/bst.h>

static int int_cmpr(void *a, void *b) {
	int ia = *(int*)a;
	int ib = *(int*)b;
	if (ia < ib) return -1;
	if (ia > ib) return 1;
	return 0;
}

static void test_ins_grt(void) {
	bst *tree = bst_construct(int_cmpr);
	int val1 = 10, val2 = 20;

	bst_insert(tree, &val1, sizeof(int));
	bst_insert(tree, &val2, sizeof(int));

	int *res = (int*)bst_search(tree, &val2);
	assert(res != NULL);
	assert(*res == 20);

	assert(tree->head != NULL);
	assert(*(int*)tree->head->data == 10);
	assert(tree->head->next != NULL);
	assert(*(int*)tree->head->next->data == 20);

	bst_destruct(tree);
	fprintf(stdout, "[%s]: debug passed test_ins_grt\n", __func__);
}

int main(void) {
	fprintf(stdout, "[%s]: debug running bst tests\n", __func__);
	test_ins_grt();
	fprintf(stdout, "[%s]: debug all bst tests passed\n", __func__);
	return 0;
}
