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
#include <string.h>

#include "opal-ud-scn.h"
#include "print_helpers.h"

int parse_ud_scn(struct opal_ud_scn **r_ud,
                 const struct opal_v6_hdr *hdr,
                 const char *buf, int buflen)
{
	struct opal_ud_scn *ud;
	struct opal_ud_scn *bufud = (struct opal_ud_scn *)buf;

	if (buflen < sizeof(struct opal_ud_scn)) {
		fprintf(stderr, "%s: corrupted, expected length >= %lu, got %u\n",
		        __func__, sizeof(struct opal_ud_scn), buflen);
		return -EINVAL;
	}

	*r_ud = malloc(hdr->length);
	if (!*r_ud)
		return -ENOMEM;
	ud = *r_ud;

	ud->v6hdr = *hdr;
	memcpy(ud->data, bufud->data, hdr->length - sizeof(struct opal_v6_hdr));

	return 0;
}

int print_ud_scn(const struct opal_ud_scn *ud, void *cookie)
{
	print_header("User Defined Data");
	print_opal_v6_hdr(ud->v6hdr);
	/*FIXME this data should be parsable if documentation appears/exists
	 * In the mean time, just dump it in hex
	 */
	print_line("User data hex","length %d",ud->v6hdr.length - 8);
	print_hex(ud->data, ud->v6hdr.length - 8);
	return 0;
}
