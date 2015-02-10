/*
 *  libopalevents - OPAL Event parsing and printing library
 *  Copyright (C) 2015 IBM Corporation

 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.

 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.

 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 *  USA
 */

#ifndef _H_OPAL_PRINT_HELPERS
#define _H_OPAL_PRINT_HELPERS

#include <stdint.h>

#define LINE_LENGTH 81
#define TITLE_LENGTH 29
#define ARG_LENGTH (LINE_LENGTH - TITLE_LENGTH)

int print_bar(void);

int print_center(const char *output);

int print_header(const char *header);

int print_hex(const uint8_t *values, int len);

int print_line(char *entry, const char *format, ...)
   __attribute__ ((format (printf, 2, 3)));

#endif /* _H_OPAL_PRINT_HELPERS */
