#include "../dictionary/dictionary.h"

int compare(void *data_fir, void *data_sec);
void recurse_print(struct node *node);


int main(void) {

	struct dictionary dict = dict_constructor(&compare);
	printf("=== inserting data ===");

	int key_arr[5] = {0, 1, 2, 3, 4};
	int val_arr[5] = {12, 32, 43, 54, 12};

	for(int i = 0; i <= 5; i++) {
		printf("%d\n", i);
		dict.dict_insert(&dict, &key_arr[i], sizeof(int), &val_arr[i], sizeof(int));
		printf("entry with {%d, %d} key, value pair created\n", key_arr[i], val_arr[i]);
	}

	printf("=== dictionary created ===\n");
	printf("=== printing dictionary ===\n");

	recurse_print(dict.tree.head);

	struct entry *element = dict.dict_search(&dict, (void *)2);
	//  FIX: here entry casting isn't working? nvm nothing is working here.
}

void recurse_print(struct node *node) {
    if (node == NULL) return;

    struct entry *entry = (struct entry *)node->data; //  FIX: maybe this works?

    int key = *(int *)entry->key;
    int value = *(int *)entry->value;

    recurse_print(node->previous);
    printf("{ key: %d, value: %d }\n", key, value);
    recurse_print(node->next);
}

int compare(void *data_fir, void *data_sec) {

	int a = *(int *)data_fir;
	int b = *(int *)data_sec;

	if (a < b) return -1;
	if (a > b) return 1;

	return 0;
}
