#
# Common Makefile definitions
#
Q =

ifndef V
Q = @
else
ifeq ($(V),0)
Q = @
endif
endif

PWD = $(shell echo `pwd`)
INSTALL = /usr/bin/install
DOXYGEN = `which doxygen`
LIB_NAME = libopalevents
# TODO RPMs

# Standard base directory names
BIN_DIR = /usr/bin
SBIN_DIR = /usr/sbin
LIB_DIR = /usr/lib
INC_DIR = /usr/include
DOC_DIR = /usr/share/doc/packages/$(PROJECT)
MAN_DIR = /usr/share/man/man8

# You should always build with -Wall
CFLAGS += -Wall -Werror -fPIC -DPIC

# Uncomment this for debug builds
# CFLAGS += -g -DDEBUG

# Define "CLEAN" as rm plus any files defined in this file that
# the actual Makefile may not (or have to) know about
CLEAN = @echo ""

# Default target for building object files
%.o: %.c
	@echo "CC $@"
	$(Q)$(CC) -c $(CFLAGS) $<


