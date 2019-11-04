CC=gcc

RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g

DEPS= tree_ops_test.c tree_ops.c

all: tree_ops_release tree_ops_debug

tree_ops_release: tree_ops.c tree_ops_test.c
	$(CC) $(RELEASE_FLAGS) $(DEPS) -o tree_ops_release.out

tree_ops_debug: tree_ops.c tree_ops_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -o tree_ops_debug.out

val: tree_ops.c tree_ops_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -o tree_ops_debug.out && valgrind --leak-check=yes --track-origins=yes ./tree_ops_debug.out

clean:
	rm -f *.out
