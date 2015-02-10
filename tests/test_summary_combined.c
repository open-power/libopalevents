#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "libopalevents-1.0/libopalevents.h"
#include "test.h"

void test_summary_combined(void *cookie)
{
	int n, i = 0;
	struct dirent **files;

	opal_event *event;
	char *buf = NULL;
	off_t size;
	int ret;

	opal_event_summarise_hdr();
	n = scandir (TEST_INPUT_DIR, &files, NULL, alphasort);
	while (i < n) {
		int fsize = 512;
		char *file = malloc(fsize);
		if (!file)
			test_fail("Couldn't malloc filename\n");

		if (files[i]->d_type != DT_REG) {
			free(files[i]);
			i++;
			continue;
		}

		int oldfsize = fsize;
		if (fsize = snprintf(file, fsize, "%s%s", TEST_INPUT_DIR, files[i]->d_name) >= oldfsize) {
			file = malloc(fsize);
			assert(file);
			snprintf(file, fsize, "%s%s", TEST_INPUT_DIR, files[i]->d_name);
		} else {
			fsize = oldfsize;
		}
		size = test_open_file(file, &buf);

		event = opal_event_create();

		opal_event_parse(event, buf, size);
		ret = opal_event_summarise(event, OPAL_EVENT_ALL);
		if (ret)
			printf("|Couldn't opal_event_summarise for file %s ret=%d              |\n", files[i]->d_name, ret);

		opal_event_destroy(event);

		/*
		 * Important to set it to NULL so that when the test suite frees it
		 * nothing bad happens
		 */
		free(buf);
		buf = NULL;

		free(files[i]);
		free(file);
		i++;
	}

	if (n < 0) {
		/* could not open drectory */
		test_fail("Could not open test file directory '%s'", TEST_INPUT_DIR);
	} else {
		free(files);
	}

	test_assert_diff();

	test_passed();
}


int main(int argc, char *argv[])
{
	TEST the_t = {
		.name = "test_summary_combined",
		.t = &test_summary_combined,
		.cookie = (void *) 0, /* Unused */
		.r = { "test_summary_combined.out", "test_summary_combined.err" },
		.i = { "" } /* Unused */
	};

	return test_main(the_t);
}
