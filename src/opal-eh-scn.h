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

#ifndef _H_OPAL_EH_SCN
#define _H_OPAL_EH_SCN

#include "opal-v6-hdr.h"
#include "opal-mtms-struct.h"
#include "opal-datetime.h"

#define OPAL_VER_LEN 16

/* Extended header section */
struct opal_eh_scn {
	struct   opal_v6_hdr v6hdr;
	struct opal_mtms_struct mtms;
	char  opal_release_version[OPAL_VER_LEN]; /* Null terminated */
	char  opal_subsys_version[OPAL_VER_LEN];  /* Null terminated */
	uint32_t reserved_0;
	struct opal_datetime event_ref_datetime;
	uint16_t reserved_1;
	uint8_t reserved_2;
	uint8_t opal_symid_len;
	char  opalsymid[0];                       /* variable sized */
} __attribute__((packed));

int parse_eh_scn(struct opal_eh_scn **r_eh,
                 const struct opal_v6_hdr *hdr,
                 const char *buf, int buflen);

int print_eh_scn(const struct opal_eh_scn *eh, void *cookie);

#endif /* _H_OPAL_EH_SCN */
