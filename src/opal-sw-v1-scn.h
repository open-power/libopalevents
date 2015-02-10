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

#ifndef _H_OPAL_SW_V1_SCN
#define _H_OPAL_SW_V1_SCN

#include <inttypes.h>

struct opal_sw_v1_scn {
	uint32_t rc;
	uint32_t line_num;
	uint32_t object_id;
	uint8_t id_length;
	char file_id[0]; /* Variable length, NULL terminated, padded to 4 bytes */
} __attribute__((packed));

#endif /* _H_OPAL_SW_V1_SCN */
