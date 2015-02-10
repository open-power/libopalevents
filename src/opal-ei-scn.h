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

#ifndef _H_OPAL_EI_SCN
#define _H_OPAL_EI_SCN

#include "opal-v6-hdr.h"

struct opal_ei_env_scn {
	uint32_t corrosion;
	uint16_t temperature;
	uint16_t rate;
} __attribute__((packed));

#define CORROSION_RATE_NORM  0x00
#define CORROSION_RATE_ABOVE 0x01

struct opal_ei_scn {
	struct opal_v6_hdr v6hdr;
	uint64_t g_timestamp;
	struct opal_ei_env_scn genesis;
	uint8_t status;
	uint8_t user_data_scn;
	uint16_t read_count;
	struct opal_ei_env_scn readings[0]; /* variable length */
} __attribute__((packed));

int parse_ei_scn(struct opal_ei_scn **r_ei,
                 struct opal_v6_hdr *hdr,
                 const char *buf, int buflen);

int print_ei_scn(const struct opal_ei_scn *ei, void *cookie);

#endif /* _H_OPAL_EI_SCN */
