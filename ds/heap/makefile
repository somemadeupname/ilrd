CC=gcc

RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g

DEPS= heap_test.c heap.c

all: heap_debug

heap_release: heap.c heap_test.c
	$(CC) $(RELEASE_FLAGS) $(DEPS) -I ../vector -L/home/student0/ran-shieber/ds/heap -lvector -o heap_release.out

heap_debug: heap.c heap_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -I ../vector -L/home/student0/ran-shieber/ds/heap -lvector -o heap_debug.out

val: heap.c heap_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -I ../vector -L/home/student0/ran-shieber/ds/heap -lvector -o heap_debug.out && valgrind --leak-check=yes --track-origins=yes ./heap_debug.out

clean:
	rm -f *.out
