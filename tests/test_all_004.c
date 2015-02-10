#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libopalevents-1.0/libopalevents.h"
#include "test.h"
#include "test_fns.h"

int main(int argc, char *argv[])
{
	TEST the_t = {
		.name = "test_all_004 (5055ed2e)",
		.t = &test_all_normal,
		.cookie = (void *) 0,
		.r = { "test_all_004.out", "test_all_004.err" },
		.i = { "test_all_004.raw" }
	};

	return test_main(the_t);
}
