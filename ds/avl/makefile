CC=gcc

RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g

DEPS= avl_test.c avl.c

all: avl_debug

avl_release: avl.c avl_test.c
	$(CC) $(RELEASE_FLAGS) $(DEPS) -o avl_release.out

avl_debug: avl.c avl_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -o avl_debug.out

val: avl.c avl_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -o avl_debug.out && valgrind --leak-check=yes --track-origins=yes ./avl_debug.out 
clean:
	rm -f *.out
