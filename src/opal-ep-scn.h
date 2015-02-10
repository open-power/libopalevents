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

#ifndef _H_OPAL_EP_SCN
#define _H_OPAL_EP_SCN

#include "opal-v6-hdr.h"

#define OPAL_EP_VALUE_SHIFT 4
#define OPAL_EP_ACTION_BITS 0x0F
#define OPAL_EP_VALUE_SET 3

#define OPAL_EP_EVENT_BITS 0x0F
#define OPAL_EP_EVENT_SHIFT 4

#define OPAL_EP_HDR_V 0x02

struct opal_ep_scn {
	struct opal_v6_hdr v6hdr;
	uint8_t value;
	uint8_t modifier;
	uint16_t ext_modifier;
	uint32_t reason;
} __attribute__((packed));

int parse_ep_scn(struct opal_ep_scn **r_ep,
                 const struct opal_v6_hdr *hdr,
                 const char *buf, int buflen);

int print_ep_scn(const struct opal_ep_scn *ep, void *cookie);

#endif /* _H_OPAL_EP_SCN */
