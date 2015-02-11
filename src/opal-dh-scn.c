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

#include "opal-dh-scn.h"
#include "parse_helpers.h"
#include "opal-event-data.h"
#include "print_helpers.h"

int parse_dh_scn(struct opal_dh_scn **r_dh,
                 struct opal_v6_hdr *hdr,
                 const char *buf, int buflen)
{
	struct opal_dh_scn *dhbuf = (struct opal_dh_scn *)buf;
	struct opal_dh_scn *dh;

	if (check_buflen(buflen, sizeof(struct opal_dh_scn) - DH_DUMP_STR_MAX,
	    __func__) < 0)
		return -EINVAL;

	*r_dh = malloc(sizeof(struct opal_dh_scn));
	if(!*r_dh)
		return -ENOMEM;
	dh = *r_dh;

	dh->v6hdr = *hdr;
	dh->dump_id = be32toh(dhbuf->dump_id);
	dh->flags = dhbuf->flags;
	dh->length_dump_os = dhbuf->length_dump_os;
	dh->dump_size = be64toh(dhbuf->dump_size);
	if (dh->flags & DH_FLAG_DUMP_HEX) {
		if (check_buflen(buflen, sizeof(struct opal_dh_scn) + sizeof(uint32_t),
		    __func__) < 0) {
			free(dh);
			return -EINVAL;
		}
		dh->shared.dump_hex = be32toh(dh->shared.dump_hex);
	} else { /* therefore it is in ascii */
		if (check_buflen(buflen, sizeof(struct opal_dh_scn) + dh->length_dump_os,
		    __func__) < 0) {
			free(dh);
			return -EINVAL;
		}
		memcpy(dh->shared.dump_str, dhbuf->shared.dump_str, dh->length_dump_os);
	}
	return 0;
}

int print_dh_scn(const struct opal_dh_scn *dh, void *cookie)
{
	print_header("Dump Locator");
	print_opal_v6_hdr(dh->v6hdr);
	print_line("Dump Type", "%s", get_dh_type_desc(dh->v6hdr.subtype));
	print_line("Dump Identifier", "0x%08x", dh->dump_id);
	print_line("Dump Flags", "0x%02x", dh->flags);
	print_line("OS Dump Length", "0x%02x", dh->length_dump_os);
	print_line("Dump Size", "0x%016lx", dh->dump_size);
	if (dh->flags & DH_FLAG_DUMP_HEX)
		print_line("OS Assigned Dump ID", "0x%08x", dh->shared.dump_hex);
	else /* therefore ascii */
		print_line("OS Assigned Dump File", "%s", dh->shared.dump_str);

	return 0;
}
