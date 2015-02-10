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

#ifndef _H_OPAL_PRIV_HEADER
#define _H_OPAL_PRIV_HEADER

#include "opal-v6-hdr.h"
#include "opal-datetime.h"

#define OPAL_PH_CREAT_SERVICE_PROC   'E'
#define OPAL_PH_CREAT_HYPERVISOR     'H'
#define OPAL_PH_CREAT_POWER_CONTROL  'W'
#define OPAL_PH_CREAT_PARTITION_FW   'L'

/* Private Header section */
struct opal_priv_hdr_scn {
	struct opal_v6_hdr v6hdr;
	struct opal_datetime create_datetime;
	struct opal_datetime commit_datetime;
	uint8_t creator_id;     /* subsystem component id */
	uint8_t reserved0;
	uint8_t reserved1;
	uint8_t scn_count;      /* number of sections in log */
	uint32_t reserved2;
	uint32_t creator_subid_hi;
	uint32_t creator_subid_lo;
	uint32_t plid;          /* platform log id */
	uint32_t log_entry_id;  /* Unique log entry id */
} __attribute__((packed));

int parse_priv_hdr_scn(struct opal_priv_hdr_scn **r_privhdr,
                       const struct opal_v6_hdr *hdr, const char *buf,
                       int buflen);

int print_priv_hdr_scn(const struct opal_priv_hdr_scn *privhdr, void *cookie);
#endif /* _H_OPAL_PRIV_HEADER */
