CC=gcc

RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g

DEPS= search_test.c search.c

all: search_release search_debug

search_release: search.c search_test.c
	$(CC) $(RELEASE_FLAGS) $(DEPS) -o search_release.out -lm

search_debug: search.c search_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -o search_debug.out -lm

val: search.c search_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -o search_debug.out -lm && valgrind --leak-check=yes --track-origins=yes ./search_debug.out

clean:
	rm -f *.out
