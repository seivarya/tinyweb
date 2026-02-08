# ======================
#  Compiler & Flags
# ======================

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
	 -Iinclude -Isrc/structures

LDFLAGS = -fsanitize=undefined,address,leak -lm

# ======================
#  Source files
# ======================

SERVER_SRC = src/server/server.c

# ======================
#  Tests
# ======================

SERVER_TEST = tests/test.c

# ======================
#  Build rules
# ======================

all: run_server

run_server: $(SERVER_SRC) $(SERVER_TEST)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# ======================
#  Cleanup
# ======================

clean:
	rm run_server 
	find . -name '*.o' -delete

.PHONY: all clean
