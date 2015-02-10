#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libopalevents-1.0/libopalevents.h"
#include "test.h"
#include "test_fns.h"

int main(int argc, char *argv[])
{
	TEST the_t = {
		.name = "basic test",
		.t = &test_parse_basic,
		.cookie = (void *) -22,
		.r = { "", "" },
		.i = { "test_parse_000.raw" }
	};

	return test_main(the_t);
}
