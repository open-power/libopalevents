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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "opal-lr-scn.h"
#include "opal-event-data.h"
#include "print_helpers.h"

int parse_lr_scn(struct opal_lr_scn **r_lr,
                 struct opal_v6_hdr *hdr, const char *buf, int buflen)
{
	struct opal_lr_scn *lrbuf = (struct opal_lr_scn *)buf;
	struct opal_lr_scn *lr;

	if (buflen < sizeof(struct opal_lr_scn)) {
		fprintf(stderr, "%s: corrupted, expected length => %lu, got %u\n",
	           __func__, sizeof(struct opal_lr_scn), buflen);
		return -EINVAL;
	}

	*r_lr = malloc(sizeof(struct opal_lr_scn));
	if (!*r_lr)
		return -ENOMEM;
	lr = *r_lr;

	lr->v6hdr = *hdr;
	lr->res_type = lrbuf->res_type;
	lr->capacity = be16toh(lrbuf->capacity);
	lr->shared = be32toh(lrbuf->shared);
	lr->memory_addr = be32toh(lrbuf->memory_addr);

	return 0;
}

int print_lr_scn(const struct opal_lr_scn *lr, void *cookie)
{
	print_header("Logical Resource");
	print_opal_v6_hdr(lr->v6hdr);
	print_line("Resource Type", "%s", get_lr_res_desc(lr->res_type));
	if (lr->res_type & LR_RES_TYPE_SHARED_PROC)
		print_line("Entitled Capacity", "0x%04x", lr->capacity);
	if (lr->res_type & LR_RES_TYPE_PROC)
		print_line("Logical CPU ID", "0x%08x", lr->shared);
	if (lr->res_type & LR_RES_TYPE_MEMORY_LMB)
		print_line("DRC Index", "0x%08x", lr->shared);
	if (lr->res_type & LR_RES_TYPE_MEMORY_PAGE) {
		print_line("Memory Logical Address  0-31", "0x%08x", lr->shared);
		print_line("Memory Logical Address 32-63", "0x%08x", lr->memory_addr);
	}

	return 0;
}
