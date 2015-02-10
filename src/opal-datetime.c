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

#include <endian.h>

#include "opal-datetime.h"
#include "parse_helpers.h"

struct opal_datetime parse_opal_datetime(const struct opal_datetime in)
{
	struct opal_datetime out;

	out.year       = from_bcd16(be16toh(in.year));
	out.month      = from_bcd8(in.month);
	out.day        = from_bcd8(in.day);
	out.hour       = from_bcd8(in.hour);
	out.minutes    = from_bcd8(in.minutes);
	out.seconds    = from_bcd8(in.seconds);
	out.hundredths = from_bcd8(in.hundredths);

	return out;
}
