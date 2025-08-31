# ===========================
# Compiler and flags
# ===========================
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# ===========================
# Source directories
# ===========================
DS_DIR = data_structures
LL_DIR = $(DS_DIR)/list
QUEUE_DIR = $(DS_DIR)/queue
NODE_DIR = $(DS_DIR)/node
TEST_DIR = $(DS_DIR)/tests
BINARY_TREE_DIR = $(DS_DIR)/tree
# ===========================
# Source files
# ===========================
LL_SRCS = $(LL_DIR)/linked_list.c
QUEUE_SRCS = $(QUEUE_DIR)/queue.c
NODE_SRCS = $(NODE_DIR)/node.c
BINARY_TREE_SRCS = $(BINARY_TREE_DIR)/binary_tree.c

LL_HEADERS = $(LL_DIR)/linked_list.h $(NODE_DIR)/node.h
QUEUE_HEADERS = $(QUEUE_DIR)/queue.h $(LL_HEADERS)
BINARY_TREE_HEADERS = $(BINARY_TREE_DIR)/binary_tree.h $(NODE_DIR)/node.h

# ===========================
# Executables
# ===========================
LIST_TEST = test_list
QUEUE_TEST = test_queue
BINARY_TREE_TEST = test_binary_tree

# ===========================
# Default target
# ===========================
all: $(LIST_TEST) $(QUEUE_TEST) $(BINARY_TREE_TEST)

# ===========================
# Compile linked list test
# ===========================
$(LIST_TEST): $(LL_SRCS) $(NODE_SRCS) $(TEST_DIR)/test_list.c $(LL_HEADERS)
	$(CC) $(CFLAGS) -I$(LL_DIR) -I$(NODE_DIR) -o $@ \
		$(TEST_DIR)/test_list.c $(LL_SRCS) $(NODE_SRCS)

# ===========================
# Compile queue test
# ===========================
$(QUEUE_TEST): $(QUEUE_SRCS) $(LL_SRCS) $(NODE_SRCS) $(TEST_DIR)/test_queue.c $(QUEUE_HEADERS)
	$(CC) $(CFLAGS) -I$(QUEUE_DIR) -I$(LL_DIR) -I$(NODE_DIR) -o $@ \
		$(TEST_DIR)/test_queue.c $(QUEUE_SRCS) $(LL_SRCS) $(NODE_SRCS)

# ===========================
# Compile binary tree test
# ===========================
$(BINARY_TREE_TEST): $(BINARY_TREE_SRCS) $(NODE_SRCS) $(TEST_DIR)/test_binary_tree.c $(BINARY_TREE_HEADERS)
	$(CC) $(CFLAGS) -I$(BINARY_TREE_DIR) -I$(NODE_DIR) -o $@ \
		$(TEST_DIR)/test_binary_tree.c $(BINARY_TREE_SRCS) $(NODE_SRCS)

# ===========================
# Clean target
# ===========================
clean:
	rm -f $(LIST_TEST) $(QUEUE_TEST) $(BINARY_TREE_TEST)

# ===========================
# Phony targets
# ===========================
.PHONY: all clean
