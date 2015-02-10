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

#ifndef _H_OPAL_DATETIME
#define _H_OPAL_DATETIME

#include <inttypes.h>

/* This comes in BCD for some reason, we convert it in parsing */
struct opal_datetime {
	uint16_t year;
	uint8_t  month;
	uint8_t  day;
	uint8_t  hour;
	uint8_t  minutes;
	uint8_t  seconds;
	uint8_t  hundredths;
} __attribute__((packed));

struct opal_datetime parse_opal_datetime(const struct opal_datetime in);

#endif /* _H_OPAL_DATETIME */
