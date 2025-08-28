# ===========================
# Compiler and flags
# ===========================
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# ===========================
# Source files
# ===========================
SRCS = linked_list.c node.c queue.c
HEADERS = linked_list.h node.h queue.h

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
$(LIST_TEST): $(SRCS) test_list.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ test_list.c linked_list.c node.c

# ===========================
# Compile queue test
# ===========================
$(QUEUE_TEST): $(SRCS) test_queue.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ test_queue.c queue.c node.c linked_list.c

# ===========================
# Clean target
# ===========================
clean:
	rm -f $(LIST_TEST) $(QUEUE_TEST) *.o

# ===========================
# Phony targets
# ===========================
.PHONY: all clean

