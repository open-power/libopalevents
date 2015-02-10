#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include "test.h"

#define SNPRINTF_SIZE 512

#define TEST_NAME "libopalevent-test"
#define STDERR_NAME "/tmp/"TEST_NAME".err-XXXXXX"
#define STDOUT_NAME "/tmp/"TEST_NAME".out-XXXXXX"

/* The file streams to the read stdout and stderr */
FILE *my_stdout;
FILE *my_stderr;

TEST cur;
int passed = 0;
char **opened_buf = NULL;

char testoutn[] = STDOUT_NAME;
char testerrn[] = STDERR_NAME;

/* Per test descriptor to stdout and stderr files */
int outfd;
int errfd;

void test_setup(void)
{
	strcpy(testoutn, STDOUT_NAME);
	strcpy(testerrn, STDERR_NAME);
	outfd = mkstemp(testoutn);
	outfd = dup2(outfd, STDOUT_FILENO);
	errfd = mkstemp(testerrn);
	errfd = dup2(errfd, STDERR_FILENO);
	if (outfd == -1 || errfd == -1) {
		fprintf(my_stderr, "%s test suite: error, couldn't open output files\n", TEST_NAME);
		exit(1);
	}
	opened_buf = NULL;
	passed = 0;

}

void test_cleanup(void)
{
	if (!passed)
		fprintf(my_stderr, "%s test suite: warning, test %s was not marked as "
		        "passed and yet has finished running\n", TEST_NAME, cur.name);
	if (opened_buf)
		free(*opened_buf);
	opened_buf = NULL;
	close(outfd);
	close(errfd);
	remove(testoutn);
	remove(testerrn);
}

void test_do(void)
{
	test_setup();
	cur.t(cur.cookie);
	test_cleanup();
}

void vtest_show(const char *fmt, va_list args)
{
	fprintf(my_stdout, "test %s: ", cur.name ? cur.name : "?");
	vfprintf(my_stdout, fmt, args);
}

void test_show(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vtest_show(fmt, args);
	va_end(args);
}

void test_assert(int result, int value)
{
	if (result != value) {
		test_show("assert (%d == %d) FAILED\n", result, value);
		exit(1);
	}
}

static void show_diff(char *difffname)
{
	char diffline[512];
	FILE *difffile;

	difffile = fopen(difffname, "r");
	if (!difffile) {
		test_show("Error couldn't open %s to display the diff\n", difffname);
		return;
	}
	test_show("!diff follows\n");
	while (fgets(diffline, sizeof(diffline), difffile)) {
		/* Call fprintf directly here because we unmodified diff output */
		fprintf(my_stdout, "%s", diffline);
	}
	fclose(difffile);
	test_show("!diff end\n");
}

static void diff_file(const char *file, const char *outfile, const char *msg)
{
	char *diffcmd = malloc(SNPRINTF_SIZE);
	char *difffname = malloc(SNPRINTF_SIZE);
	int total_size;

	assert(file && outfile);
	assert(diffcmd && difffname);

	if (total_size = snprintf(difffname, SNPRINTF_SIZE, "%s.diff", outfile) >= SNPRINTF_SIZE) {
		difffname = malloc(total_size);
		assert(difffname);
		snprintf(difffname, total_size, "%s.diff", outfile);
	}

	if (total_size = snprintf(diffcmd, SNPRINTF_SIZE, "diff -N \"%s%s\" \"%s\" >> \"%s\"",
                             TEST_RESULT_DIR, file, outfile, difffname) >= SNPRINTF_SIZE) {
		diffcmd = malloc(total_size);
		assert(diffcmd);
		snprintf(diffcmd, total_size, "diff -N \"%s%s\" \"%s\" >> \"%s\"",
               TEST_RESULT_DIR, file, outfile, difffname);
	}
	if (system(diffcmd)) {
		test_show(msg);
		show_diff(difffname);
		free(difffname);
		free(diffcmd);
		exit(1);
	}
	free(difffname);
	free(diffcmd);
	remove(difffname);
}

void test_assert_diff(void)
{

	fflush(stderr);
	fflush(stdout);

	if (*(cur.r.out) != '\0') {
		diff_file(cur.r.out, testoutn, "STDOUT diff failed\n");
	}

	if (*(cur.r.err) != '\0') {
		diff_file(cur.r.err, testerrn, "STDERR diff failed\n");
	}
}

void test_passed(void)
{
	test_show("PASSED\n");
	passed = 1;
}

void test_fail(const char *fmt, ...)
{
	va_list args;
	if (fmt) {
		va_start(args, fmt);
		vtest_show(fmt, args);
		va_end(args);
	}
	test_show("FAIL");
	exit(1);
}

off_t test_open(char **buf)
{
	assert(buf);
	char file[512];
	snprintf(file, sizeof(file), "%s%s", TEST_INPUT_DIR, cur.i.in);
	return test_open_file(file, buf);
}

off_t test_open_file(const char *file, char **buf)
{
	assert(file && buf);
	off_t size;
	struct stat st;
	if (stat(file, &st) != 0)
		test_fail("couldn't stat test input file %s\n", file);
	size = st.st_size;
	*buf = malloc(size);
	if (!(*buf))
		test_fail("couldn't malloc input file\n");
	opened_buf = buf;
	int fd = open(file, O_RDONLY);
	if (fd <= 0)
		test_fail("couldn't open test input file %s\n", file);

	int sz = 0;
	while (sz < size) {
		int r = read(fd, (*buf) + sz, size - sz);
		if (r < 0)
			test_fail("couldn't read test input file %s (errno: %d)\n", file, errno);
		sz += r;
	}
	close(fd);
	return size;
}

int test_main(TEST t)
{
	int orig_outfd = dup(STDOUT_FILENO);
	int orig_errfd = dup(STDERR_FILENO);
	my_stderr = fdopen(orig_errfd, "w");
	my_stdout = fdopen(orig_outfd, "w");

	cur = t;
	test_do();

	fclose(my_stderr);
	fclose(my_stdout);
	close(orig_outfd);
	close(orig_errfd);
	return 0;
}

