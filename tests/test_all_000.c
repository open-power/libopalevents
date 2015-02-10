#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libopalevents-1.0/libopalevents.h"
#include "test.h"

void test_all_000(void *cookie)
{
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
	int value = (int) cookie;
#pragma GCC diagnostic pop
	opal_event *event = opal_event_create();
	if (!event)
		test_fail("Unexpected NULL\n");
	char *buf;
	off_t size = test_open(&buf);
	int ret = opal_event_parse(event, buf, size);

	test_assert(ret, value);

	opal_event_print(event);

	test_assert_diff();
	test_passed();
}

int main(int argc, char *argv[])
{
	TEST the_t = {
		.name = "test_all_000",
		.t = &test_all_000,
		.cookie = (void *) 16,
		.r = { "test_all_000.out", "test_all_000.err" },
		.i = { "test_all_000.raw" }
	};

	return test_main(the_t);
}
