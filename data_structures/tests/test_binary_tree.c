#include "../tree/binary_tree.h"

int compare(void *data_fir, void *data_sec);

int main(void) {

	struct binary_tree tree = binary_tree_constructor(&compare);
	printf("=== binary tree constructed ===\n");
	binary_tree_destructor(&tree);
	
	

	int data_array[20] = {
		23, 43, 21, 54, 76,
		12, 32, 46, 75, 87,
		98, 11, 29, 61, 72,
		34, 57, 68, 90, 100
	};

	for (int i = 0; i < 20; i++) {
		tree.insert(&tree, &data_array[i], sizeof(int));
		//  FIX: node already exists on first iteration, *direction variable is the issue
		printf("data: %d inserted at index:: %d\n", data_array[i], i);

	}
}

int compare(void *data_fir, void *data_sec) {
    int a = *(int *)data_fir;
    int b = *(int *)data_sec;

    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}
