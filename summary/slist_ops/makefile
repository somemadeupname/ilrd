CC=gcc

RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g

DEPS= slist_ops_test.c slist_ops.c

all: slist_ops_release slist_ops_debug

slist_ops_release: slist_ops.c slist_ops_test.c
	$(CC) $(RELEASE_FLAGS) $(DEPS) -o slist_ops_release.out

slist_ops_debug: slist_ops.c slist_ops_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -o slist_ops_debug.out

val: slist_ops.c slist_ops_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -o slist_ops_debug.out && valgrind --leak-check=yes --track-origins=yes ./slist_ops_debug.out

clean:
	rm -f *.out
