#ifndef _H_TEST
#define _H_TEST

typedef struct {
	const char *out;
	const char *err;
} test_result_files;

typedef struct {
	const char *in;
} test_input_files;

typedef struct {
	const char *name;
	void (*t)(void *cookie);
	void *cookie;
	test_result_files r;
	test_input_files i;
} TEST;

#define TEST_RESULT_DIR DATADIR"tests/results/"
#define TEST_INPUT_DIR DATADIR"tests/input/"

off_t test_open_file(const char *file, char **buf);

off_t test_open(char **buf);

void test_show(const char *fmt, ...);

void test_assert(int result, int value);

void test_assert_diff();

void test_passed();

void test_fail(const char *fmt, ...);

int test_main(TEST t);
#endif /* _H_TEST */
