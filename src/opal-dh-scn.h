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

#ifndef _H_OPAL_DH_SCN
#define _H_OPAL_DH_SCN

#include "opal-v6-hdr.h"

#define DH_FLAG_DUMP_HEX 0x40

#define DH_DUMP_STR_MAX 40

struct opal_dh_scn {
	struct opal_v6_hdr v6hdr;
	uint32_t dump_id;
	uint8_t flags;
	uint8_t reserved[2];
	uint8_t length_dump_os;
	uint64_t dump_size;
	union {
		char dump_str[DH_DUMP_STR_MAX];
		uint32_t dump_hex;
	} shared;
} __attribute__((packed));

int parse_dh_scn(struct opal_dh_scn **r_dh,
                 struct opal_v6_hdr *hdr,
                 const char *buf, int buflen);

int print_dh_scn(const struct opal_dh_scn *dh, void *cookie);

#endif /* _H_OPAL_DH_SCN */
