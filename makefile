#  compiler & flags

CC = gcc

CFLAGS = -g3 -ggdb -O1 \
	 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wconversion \
	 -Wnull-dereference -Wdouble-promotion -Wimplicit-fallthrough \
	 -Wcast-align -Wstrict-aliasing=3 -Wstrict-prototypes -Wmissing-prototypes \
	 -Wmissing-declarations -Wunused-parameter -Wfloat-equal \
	 -Winit-self -Wuninitialized -Wswitch-enum -Wredundant-decls \
	 -Wpointer-arith -Wvla \
	 -Werror \
	 -fsanitize=address,undefined,leak,pointer-compare,pointer-subtract,alignment \
	 -fsanitize=bounds,float-cast-overflow,float-divide-by-zero \
	 -fsanitize=signed-integer-overflow \
	 -fno-omit-frame-pointer -fno-optimize-sibling-calls \
	 -fstack-protector-all -D_FORTIFY_SOURCE=2 -fPIC \
	 -std=c11 -msse -mfpmath=sse \
	 -Iinclude -Isrc/structs -Isrc/server

LDFLAGS = -fsanitize=undefined,address,leak -lm -lpthread

#  source files

CORE_SRCS = \
	src/server/server.c \
	src/server/parser.c \
	src/server/route.c \
	src/server/http.c \
	src/server/executor.c \
	src/structs/dict/dict.c \
	src/structs/dict/entry.c \
	src/structs/queue/queue.c \
	src/structs/queue/queue_node.c \
	src/structs/tree/bst.c \
	src/structs/tree/bst_node.c \
	src/structs/slist/slist.c \
	src/structs/slist/slist_node.c

CORE_OBJS = $(CORE_SRCS:.c=.o)

SERVER_MAIN = tests/test.c

TEST_EXES = test_queue test_dict test_slist test_bst test_executor test_parser

#  build rules

all: server tests

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

server: $(CORE_OBJS) $(SERVER_MAIN)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

tests: $(TEST_EXES)

test_queue: $(CORE_OBJS) tests/test_queue.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test_dict: $(CORE_OBJS) tests/test_dict.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test_slist: $(CORE_OBJS) tests/test_slist.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test_bst: $(CORE_OBJS) tests/test_bst.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test_executor: $(CORE_OBJS) tests/test_executor.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test_parser: $(CORE_OBJS) tests/test_parser.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

#  cleanup

clean:
	rm -f server $(TEST_EXES)
	find . -name '*.o' -delete

.PHONY: all clean server tests
