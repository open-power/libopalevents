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

#ifndef _H_OPAL_IE_SCN
#define _H_OPAL_IE_SCN

#include "opal-v6-hdr.h"

#define IE_TYPE_ERROR_DET 0x01
#define IE_TYPE_ERROR_REC 0x02
#define IE_TYPE_EVENT 0x03
#define IE_TYPE_RPC_PASS_THROUGH 0x04

#define IE_SUBTYPE_REBALANCE 0x01
#define IE_SUBTYPE_NODE_ONLINE 0x03
#define IE_SUBTYPE_NODE_OFFLINE 0x04
#define IE_SUBTYPE_PLAT_MAX_CHANGE 0x05

#define IE_DATA_MAX 216

struct opal_ie_scn {
	struct opal_v6_hdr v6hdr;
	uint8_t type;
	uint8_t rpc_len;
	uint8_t scope;
	uint8_t subtype;
	uint32_t drc;
	union {
		uint8_t rpc[IE_DATA_MAX];
		uint64_t max;
	} data;
} __attribute__((packed));

int parse_ie_scn(struct opal_ie_scn **r_ie,
                 struct opal_v6_hdr *hdr,
                 const char *buf, int buflen);

int print_ie_scn(const struct opal_ie_scn *ie, void *cookie);

#endif /* _H_OPAL_IE_SCN */
