#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "test.h"
#include "libopalevents-1.0/libopalevents.h"

void test_parse_basic(void *cookie)
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
	test_passed();
}

void test_parse_normal(void *cookie)
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
	test_assert_diff();
	test_passed();
}

void test_all_normal(void *cookie)
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

