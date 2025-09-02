#include "../tree/binary_tree.h"
#include <time.h>

// prototypes
int compare(void *data_fir, void *data_sec);
void recurse_print(struct node *node, int depth);
void run_basic_tests();
void run_edge_tests();
void run_random_tests();

int main(void) {
	srand((unsigned)time(NULL));

	printf("=== running basic tests ===\n");
	run_basic_tests();

	printf("\n=== running edge case tests ===\n");
	run_edge_tests();

	printf("\n=== running random stress test ===\n");
	run_random_tests();

	printf("\nall tests finished.\n");
	return 0;
}

/* ------------ tree helpers ------------ */

int compare(void *data_fir, void *data_sec) {
	int a = *(int *)data_fir;
	int b = *(int *)data_sec;

	if (a < b) return -1;
	if (a > b) return 1;
	return 0;
}

void recurse_print(struct node *node, int depth) {
	if (!node) return;

	recurse_print(node->previous, depth + 1);

	for (int i = 0; i < depth; i++) printf("  "); // indent
	printf("%d\n", *(int *)node->data);

	recurse_print(node->next, depth + 1);
}

/* ------------ test suites ------------ */

void run_basic_tests() {
	struct binary_tree tree = binary_tree_constructor(&compare);

	int data_array[10] = {23, 43, 21, 54, 12, 32, 46, 75, 11, 29};

	for (int i = 0; i < 10; i++) {
		printf("inserting %d...\n", data_array[i]);
		tree.binary_node_insert(&tree, &data_array[i], sizeof(int));

		printf("tree inorder after insert:\n");
		recurse_print(tree.head, 0);
		printf("-----\n");
	}

	// search tests
	int to_search[] = {23, 75, 11, 100, -5};
	for (int i = 0; i < 5; i++) {
		int *found = tree.binary_node_search(&tree, &to_search[i]);
		if (found) {
			printf("[*] pass search(%d) = %d\n", to_search[i], *found);
		} else {
			printf("[*] pass search(%d) = not found\n", to_search[i]);
		}
	}
}

void run_edge_tests() {
	struct binary_tree tree = binary_tree_constructor(&compare);

	int ascending[5] = {1, 2, 3, 4, 5};
	int descending[5] = {10, 9, 8, 7, 6};

	// ascending insert
	printf("\nascending insert:\n");
	for (int i = 0; i < 5; i++) {
		tree.binary_node_insert(&tree, &ascending[i], sizeof(int));
	}
	recurse_print(tree.head, 0);

	// descending insert
	struct binary_tree tree2 = binary_tree_constructor(&compare);
	printf("\ndescending insert:\n");
	for (int i = 0; i < 5; i++) {
		tree2.binary_node_insert(&tree2, &descending[i], sizeof(int));
	}
	recurse_print(tree2.head, 0);

	// duplicate insert check
	printf("\nduplicate insert test:\n");
	int dup = 42;
	tree2.binary_node_insert(&tree2, &dup, sizeof(int));
	tree2.binary_node_insert(&tree2, &dup, sizeof(int)); // should trigger "node already exists"
}

void run_random_tests() {
	struct binary_tree tree = binary_tree_constructor(&compare);

	int nums[20];
	for (int i = 0; i < 20; i++) {
		nums[i] = rand() % 100;
		tree.binary_node_insert(&tree, &nums[i], sizeof(int));
	}

	printf("tree inorder (should be sorted):\n");
	recurse_print(tree.head, 0);

	// verify search for all inserted numbers
	for (int i = 0; i < 20; i++) {
		int *found = tree.binary_node_search(&tree, &nums[i]);
		if (!found || *found != nums[i]) {
			printf("[*] fail search(%d) failed!\n", nums[i]);
		}
	}

	// search for some random numbers not likely in tree
	for (int i = 0; i < 5; i++) {
		int x = 200 + rand() % 50;
		int *found = tree.binary_node_search(&tree, &x);
		if (found) {
			printf("[*] fail search(%d) returned %d but shouldn't exist!\n", x, *found);
		} else {
			printf("[*] pass search(%d) = not found\n", x);
		}
	}
}
