CC=gcc

RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g

DEPS= semaphore_test.c semaphore.c

all: semaphore_release semaphore_debug

semaphore_release: semaphore.c semaphore_test.c
	$(CC) $(RELEASE_FLAGS) $(DEPS) -o semaphore_release.out

semaphore_debug: semaphore.c semaphore_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -o semaphore_debug.out

val: semaphore.c semaphore_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -o semaphore_debug.out && valgrind --leak-check=yes --track-origins=yes ./semaphore_debug.out

clean:
	rm -f *.out
