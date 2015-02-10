#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libopalevents-1.0/libopalevents.h"
#include "test.h"
#include "test_fns.h"

int main(int argc, char *argv[])
{
	TEST the_t = {
		.name = "test_all_002",
		.t = &test_all_normal,
		.cookie = (void *) 48,
		.r = { "test_all_002.out", "test_all_002.err" },
		.i = { "test_all_002.raw" }
	};

	return test_main(the_t);
}
