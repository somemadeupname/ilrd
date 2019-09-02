#define START_RED printf("\033[1;31m");
#define END_RED printf("\033[0m");
#define TRUE 1
#define FALSE 0

#define PREVENT_WARNINGS_FROM_UNUSED_FUNCS_FROM_TESTS_TEMPLATE \
{\
	expect_int(1,1,"hi");\
	expect_size_t(1lu,1lu,"hi");\
}

void expect_int(int result, int expected_result, char *func_name);

void expect_size_t(size_t result, size_t expected_result, char *func_name);

void expect_NULL(void *pointer, char *func_name);

void expect_Not_NULL(void *pointer, char *func_name);
