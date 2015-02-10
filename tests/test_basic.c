#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libopalevents-1.0/libopalevents.h"
#include "test.h"

void tester(void *cookie)
{
	opal_event *event = opal_event_create();
	if (!event)
		test_fail("Unexpected NULL\n");
	test_assert(1, 1);
	test_passed();
}

int main(int argc, char *argv[])
{
	TEST the_t = {
		.name = "tester",
		.t = &tester,
		.cookie = NULL,
		.r = { "", "" },
		.i = { "" }
	};

	return test_main(the_t);
}
