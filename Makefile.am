ACLOCAL_AMFLAGS = -I m4

pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = libopalevents.pc

AM_CPPFLAGS = "-I$(srcdir)/include/"

lib_LTLIBRARIES = libopalevents.la

pkginclude_HEADERS = include/libopalevents-$(VERSION)/libopalevents.h

noinst_HEADERS = src/opal-mtms-scn.h src/opal-priv-hdr-scn.h src/opal-src-fru-scn.h \
                 src/opal-lr-scn.h src/opal-eh-scn.h src/opal-ep-scn.h src/opal-sw-scn.h \
                 src/opal-ud-scn.h src/opal-hm-scn.h src/opal-ch-scn.h src/opal-lp-scn.h \
                 src/opal-ie-scn.h src/opal-mi-scn.h src/opal-ei-scn.h src/opal-ed-scn.h \
                 src/opal-dh-scn.h src/opal-usr-scn.h src/opal-src-scn.h src/opal-v6-hdr.h \
                 src/parse-opal-event.h src/opal-event-log.h src/print_helpers.h \
                 src/opal-event-data.h src/print-opal-event.h src/opal-sw-v1-scn.h \
                 src/parse_helpers.h src/opal-mtms-struct.h src/opal-datetime.h src/opal-sw-v2-scn.h

libopalevents_la_SOURCES = src/opal-mtms-scn.c src/opal-priv-hdr-scn.c src/libopalevents.c \
                           src/opal-src-fru-scn.c src/opal-usr-scn.c src/opal-src-scn.c \
                           src/opal-lr-scn.c src/opal-eh-scn.c src/opal-ep-scn.c src/opal-sw-scn.c \
                           src/opal-ud-scn.c src/opal-hm-scn.c src/opal-ch-scn.c src/opal-lp-scn.c \
                           src/opal-ie-scn.c src/opal-mi-scn.c src/opal-ei-scn.c src/opal-ed-scn.c \
                           src/opal-dh-scn.c src/opal-v6-hdr.c src/parse_helpers.c src/opal-mtms-struct.c \
                           src/parse-opal-event.c src/opal-event-log.c src/opal-datetime.c \
                           src/print_helpers.c src/opal-event-data.c src/print-opal-event.c

tests_common = tests/test.c tests/test.h tests/test_fns.c tests/test_fns.h $(include_HEADERS)

test_basic_SOURCES = tests/test_basic.c $(tests_common)
test_basic_LDADD = libopalevents.la
test_basic_CFLAGS = -DDATADIR=\"$(srcdir)/\"

test_parse_000_SOURCES = tests/test_parse_000.c $(tests_common)
test_parse_000_LDADD = libopalevents.la
test_parse_000_CFLAGS = -DDATADIR=\"$(srcdir)/\"

test_parse_001_SOURCES = tests/test_parse_001.c $(tests_common)
test_parse_001_LDADD = libopalevents.la
test_parse_001_CFLAGS = -DDATADIR=\"$(srcdir)/\"

test_parse_002_SOURCES = tests/test_parse_002.c $(tests_common)
test_parse_002_LDADD = libopalevents.la
test_parse_002_CFLAGS = -DDATADIR=\"$(srcdir)/\"

test_all_000_SOURCES = tests/test_all_000.c $(tests_common)
test_all_000_LDADD = libopalevents.la
test_all_000_CFLAGS = -DDATADIR=\"$(srcdir)/\"

test_all_001_SOURCES = tests/test_all_001.c $(tests_common)
test_all_001_LDADD = libopalevents.la
test_all_001_CFLAGS = -DDATADIR=\"$(srcdir)/\"

test_all_002_SOURCES = tests/test_all_002.c $(tests_common)
test_all_002_LDADD = libopalevents.la
test_all_002_CFLAGS = -DDATADIR=\"$(srcdir)/\"

test_all_003_SOURCES = tests/test_all_003.c $(tests_common)
test_all_003_LDADD = libopalevents.la
test_all_003_CFLAGS = -DDATADIR=\"$(srcdir)/\"

test_all_004_SOURCES = tests/test_all_004.c $(tests_common)
test_all_004_LDADD = libopalevents.la
test_all_004_CFLAGS = -DDATADIR=\"$(srcdir)/\"

test_summary_combined_SOURCES = tests/test_summary_combined.c $(tests_common)
test_summary_combined_LDADD = libopalevents.la
test_summary_combined_CFLAGS = -DDATADIR=\"$(srcdir)/\"

EXTRA_DIST = tests/input tests/results

check_PROGRAMS = test_basic test_parse_000 test_parse_001 test_parse_002 test_all_000 test_all_001 \
                 test_all_002 test_all_003 test_all_004 test_summary_combined

TESTS = $(check_PROGRAMS)
