
struct dict {
	void *key;
	void *value;
};

struct dict dict_constructor(void *key, int key_size, void *value, int value_size);

