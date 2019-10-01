CC=gcc

RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g

DEPS= hash_table_test.c hash_table.c -I ../dlist

all: hash_table_debug

hash_table_release: hash_table.c hash_table_test.c
	$(CC) $(RELEASE_FLAGS) $(DEPS) -o hash_table_release.out

hash_table_debug: hash_table.c hash_table_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -L/home/shieber/git/ran-shieber/ds/hash_table -o hash_table_debug.out -ldlist

val: hash_table.c hash_table_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -L/home/shieber/git/ran-shieber/ds/hash_table -o hash_table_debug.out -ldlist && valgrind --leak-check=yes --track-origins=yes ./hash_table_debug.out

clean:
	rm -f *.out
