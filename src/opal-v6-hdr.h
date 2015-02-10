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

#ifndef _H_OPAL_V6_HEADER
#define _H_OPAL_V6_HEADER

#include <inttypes.h>

struct opal_v6_hdr {
	char     id[2];
	uint16_t length;       /* section length */
	uint8_t  version;      /* section version */
	uint8_t  subtype;      /* section sub-type id */
	uint16_t component_id; /* component id of section creator */
} __attribute__((packed));


int parse_section_header(struct opal_v6_hdr *hdr,
                         const char *buf, int buflen);

int print_opal_v6_hdr(const struct opal_v6_hdr hdr);

#endif /* _H_OPAL_V6_HEADER */
