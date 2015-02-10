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

#include "opal-mi-scn.h"
#include "print_helpers.h"

int parse_mi_scn(struct opal_mi_scn **r_mi,
                 struct opal_v6_hdr *hdr,
                 const char *buf, int buflen)
{
	struct opal_mi_scn *mibuf = (struct opal_mi_scn *)buf;
	struct opal_mi_scn *mi;

	if (buflen < sizeof(struct opal_mi_scn)) {
		fprintf(stderr, "%s: corrupted, expected length => %lu, got %u",
		        __func__, sizeof(struct opal_mi_scn), buflen);
		return -EINVAL;
	}

	*r_mi = malloc(sizeof(struct opal_mi_scn));
	if (!*r_mi)
		return -ENOMEM;
	mi = *r_mi;

	mi->v6hdr = *hdr;
	mi->flags = be32toh(mibuf->flags);

	return 0;
}

int print_mi_scn(const struct opal_mi_scn *mi, void *cookie)
{

	print_header("Manufacturing Information");
	print_opal_v6_hdr(mi->v6hdr);
	print_line("Policy Flags", "0x%08x", mi->flags);

	return 0;
}

