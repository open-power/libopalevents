AC_INIT([libopalevents], [1.0], [cyril.bur@au1.ibm.com])
AC_PREREQ([2.63])
AC_CONFIG_SRCDIR([src/libopalevents.c])
AC_LANG([C])
AC_HEADER_STDC
AC_CONFIG_MACRO_DIR([m4])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h inttypes.h stdint.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([bzero memset])

AX_APPEND_COMPILE_FLAGS([-D_FORTIFY_SOURCE=2 -fstack-protector-all])
AX_APPEND_COMPILE_FLAGS([-fwrapv -fPIE -Wstack-protector])
AX_APPEND_COMPILE_FLAGS([--param=ssp-buffer-size=1])

LT_LANG([C])

LT_INIT

AM_PROG_CC_C_O

AM_INIT_AUTOMAKE([foreign no-dist-gzip dist-xz subdir-objects -Wall -Werror tar-ustar])

AC_CONFIG_FILES([Makefile libopalevents.pc])

AC_OUTPUT()
