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

#include <inttypes.h>
#include <stdio.h>
#include <errno.h>

uint16_t from_bcd16(uint16_t bcd)
{
	return (bcd & 0x000f) +
	       ((bcd & 0x00f0) >> 4) * 10 +
	       ((bcd & 0x0f00) >> 8) * 100 +
	       ((bcd & 0xf000) >> 12) * 1000;
}

uint8_t from_bcd8(uint8_t bcd)
{
	return (bcd & 0x0f) + ((bcd & 0xf0) >> 4) * 10;
}

/* It is imperative that this function return negative on error */
int check_buflen(int buflen, int min_length, const char *func)
{
	if (buflen < min_length) {
		fprintf(stderr, "%s: corrupted, expected minimum length %d, got %d\n",
		        func, min_length, buflen);
		return -EINVAL;
	}
	return 0;
}
