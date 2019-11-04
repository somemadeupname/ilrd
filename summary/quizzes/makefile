CC=gcc

RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
DEBUG_FLAGS=-ansi -pedantic-errors -Wall -Wextra -g

DEPS= quizzes_test.c quizzes.c

all: quizzes_release quizzes_debug

quizzes_release: quizzes.c quizzes_test.c
	$(CC) $(RELEASE_FLAGS) $(DEPS) -o quizzes_release.out

quizzes_debug: quizzes.c quizzes_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -o quizzes_debug.out

val: quizzes.c quizzes_test.c
	$(CC) $(DEBUG_FLAGS) $(DEPS) -o quizzes_debug.out && valgrind --leak-check=yes --track-origins=yes ./quizzes_debug.out

clean:
	rm -f *.out
