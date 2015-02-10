#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libopalevents-1.0/libopalevents.h"
#include "test.h"
#include "test_fns.h"

int main(int argc, char *argv[])
{
	TEST the_t = {
		.name = "test_all_003 (5032a000)",
		.t = &test_all_normal,
		.cookie = (void *) 16,
		.r = { "test_all_003.out", "test_all_003.err" },
		.i = { "test_all_003.raw" }
	};

	return test_main(the_t);
}
