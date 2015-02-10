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

#ifndef _H_OPAL_LR_SCN
#define _H_OPAL_LR_SCN

#include "opal-v6-hdr.h"

#define LR_RES_TYPE_PROC 0x10
#define LR_RES_TYPE_SHARED_PROC 0x11
#define LR_RES_TYPE_MEMORY_PAGE 0x40
#define LR_RES_TYPE_MEMORY_LMB 0x41

struct opal_lr_scn {
	struct opal_v6_hdr v6hdr;
	uint8_t res_type;
	uint8_t reserved;
	uint16_t capacity;
	uint32_t shared;
	uint32_t memory_addr;
} __attribute__((packed));

int parse_lr_scn(struct opal_lr_scn **r_lr,
                 struct opal_v6_hdr *hdr, const char *buf, int buflen);

int print_lr_scn(const struct opal_lr_scn *lr, void *cookie);

#endif /* _H_OPAL_LR_SCN */
