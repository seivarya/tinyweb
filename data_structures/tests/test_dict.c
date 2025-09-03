#include "../dictionary/dictionary.h"

int dict_compare(void *entry_ptr, void *key_ptr);
void recurse_print(struct node *node);
int compare(void *data_fir, void *data_sec);

int main(void) {

	struct dictionary dict = dict_constructor(&dict_compare); // overwriting compare with dict_compare

	int key_arr[5] = { 0, 1, 2, 3, 4 };
	int val_arr[5] = { 121, 32, 43, 53, 43 };

	for (int i = 0; i < 5; i++) {
		printf("entry added at: %d\n", i);
		dict.dict_insert(&dict, &key_arr[i], sizeof(int), &val_arr[i], sizeof(int));
	}
	printf("=== printing dictionary ===\n");
	recurse_print(dict.tree.head);

	printf("=== searching data ===\n");
	int test_key;

	printf("enter key to search: ");
	scanf("%d", &test_key);

	struct entry *searched = dict.dict_search(&dict, &test_key);
	int fetched_value = *(int *)searched->value;
	int fetched_key = *(int *)searched->key;

	printf("found entry with key: %d :: entry: { %d, %d }\n", fetched_key, fetched_key, fetched_value);
}

void recurse_print(struct node *node) {
    if (!node) return;

    recurse_print(node->previous);

    struct entry *entry = (struct entry *)node->data;
    int key   = *(int *)entry->key;
    int value = *(int *)entry->value;

    printf("{ %d: %d }\n", key, value);

    recurse_print(node->next);
}

int compare(void *data_fir, void *data_sec) {

	int a = *(int *)data_fir;
	int b = *(int *)data_sec;

	if (a < b) return -1;
	if (a > b) return 1;

	return 0;
}

int dict_compare(void *entry_ptr, void *key_ptr) {
    struct entry *e = (struct entry *)entry_ptr;
    return compare(e->key, key_ptr);  // reuse your existing compare()
}
