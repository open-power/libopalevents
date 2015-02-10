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

#ifndef _H_OPAL_SRC_SCN
#define _H_OPAL_SRC_SCN

#include "opal-v6-hdr.h"
#include "opal-src-fru-scn.h"

#define OPAL_SRC_SCN_PRIMARY_REFCODE_LEN 32

#define OPAL_SRC_ADD_SCN 0x1
#define OPAL_SRC_FRU_MAX 10

#define OPAL_SRC_SCN_STATIC_SIZE sizeof(struct opal_src_scn) \
	- sizeof(struct opal_src_add_scn_hdr) \
	- (OPAL_SRC_FRU_MAX * sizeof(struct opal_fru_scn)) \
	- sizeof(uint8_t)

#define OPAL_FRU_MORE 0x01

struct opal_src_add_scn_hdr {
	uint8_t  id;
	uint8_t  flags;
	uint16_t length; /* This is counted in words */
} __attribute__((packed));

struct opal_src_scn {
	struct opal_v6_hdr v6hdr;
	uint8_t	version;
	uint8_t	flags;
	uint8_t	reserved_0;
	uint8_t	wordcount;
	uint16_t reserved_1;
	uint16_t srclength;
	uint32_t	ext_refcode2;
	uint32_t	ext_refcode3;
	uint32_t	ext_refcode4;
	uint32_t	ext_refcode5;
	uint32_t	ext_refcode6;
	uint32_t	ext_refcode7;
	uint32_t	ext_refcode8;
	uint32_t	ext_refcode9;
	char		primary_refcode[OPAL_SRC_SCN_PRIMARY_REFCODE_LEN];
	/* Currently there can only be one type of optional
	 * sub section, in the future this may change.
	 * This will do for now.
	 */
	struct opal_src_add_scn_hdr addhdr;
	struct opal_fru_scn fru[OPAL_SRC_FRU_MAX]; /*Optional */
	uint8_t fru_count;
} __attribute__((packed));

int parse_src_scn(struct opal_src_scn **r_src,
                  const struct opal_v6_hdr *hdr,
                  const char *buf, int buflen);

int print_src_scn(const struct opal_src_scn *src, void *cookie);

#endif /* _H_OPAL_SRC_SCN */
