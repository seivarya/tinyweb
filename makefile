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

# ===========================
# Source files
# ===========================
LL_SRCS = $(LL_DIR)/linked_list.c
QUEUE_SRCS = $(QUEUE_DIR)/queue.c
NODE_SRCS = $(NODE_DIR)/node.c

HEADERS = $(LL_DIR)/linked_list.h $(QUEUE_DIR)/queue.h $(NODE_DIR)/node.h

# ===========================
# Executables
# ===========================
LIST_TEST = test_list
QUEUE_TEST = test_queue

# ===========================
# Default target
# ===========================
all: $(LIST_TEST) $(QUEUE_TEST)

# ===========================
# Compile linked list test
# ===========================
$(LIST_TEST): $(LL_SRCS) $(NODE_SRCS) $(TEST_DIR)/test_list.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(LL_DIR) -I$(NODE_DIR) -o $@ \
	$(TEST_DIR)/test_list.c $(LL_SRCS) $(NODE_SRCS)

# ===========================
# Compile queue test
# ===========================
$(QUEUE_TEST): $(QUEUE_SRCS) $(LL_SRCS) $(NODE_SRCS) $(TEST_DIR)/test_queue.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(QUEUE_DIR) -I$(LL_DIR) -I$(NODE_DIR) -o $@ \
	$(TEST_DIR)/test_queue.c $(QUEUE_SRCS) $(LL_SRCS) $(NODE_SRCS)

# ===========================
# Clean target
# ===========================
clean:
	rm -f $(LIST_TEST) $(QUEUE_TEST)

# ===========================
# Phony targets
# ===========================
.PHONY: all clean
