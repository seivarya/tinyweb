#include "../dictionary/dictionary.h"

int compare(void *data_fir, void *data_sec);
void recurse_print(struct node *node);

//  WARNING: it won't compile because im a retard and named all structure's method same so that needs fixing.

int main(void) {
	struct dictionary dict = dict_constructor(&compare);
	printf("=== inserting data ===");
	int key_arr[5] = {0, 1, 2, 3, 4};
	int val_arr[5] = {12, 32, 43, 54, 12};

	for(int i = 0; i < 10; i++) {
		dict.insert(&dict, &key_arr[i], sizeof(int), &val_arr[i], sizeof(int));
		printf("entry with {%d, %d} key, value pair created\n", key_arr[i], val_arr[i]);
	}

	printf("=== dictionary created ===\n");
	printf("=== printing dictionary ===\n");

	recurse_print(dict.tree.head);
	
}

void recurse_print(struct node *node) {
	if (!node) {
		return;
	}
	recurse_print(node->previous);
	printf("%d/n", *(int *)node->data);
}

int compare(void *data_fir, void *data_sec) {
	int a = *(int *)data_fir;
	int b = *(int *)data_sec;

	if (a < b) return -1;
	if (a > b) return 1;
	return 0;
}


