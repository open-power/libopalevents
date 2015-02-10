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

#include "opal-ed-scn.h"
#include "parse_helpers.h"
#include "opal-event-data.h"
#include "print_helpers.h"

int parse_ed_scn(struct opal_ed_scn **r_ed,
                 struct opal_v6_hdr *hdr,
                 const char *buf, int buflen)
{
	struct opal_ed_scn *ed;
	struct opal_ed_scn *edbuf = (struct opal_ed_scn *)buf;

	if (check_buflen(buflen, sizeof(struct opal_ed_scn), __func__) < 0 ||
	    check_buflen(buflen, hdr->length, __func__) < 0 ||
	    check_buflen(hdr->length, sizeof(struct opal_ed_scn), __func__) < 0)
		return -EINVAL;
	*r_ed = malloc(hdr->length);
	if (!*r_ed)
		return -ENOMEM;
	ed = *r_ed;

	ed->v6hdr = *hdr;
	ed->creator_id = edbuf->creator_id;
	memcpy(ed->user_data, edbuf->user_data, hdr->length - 12);

	return 0;
}

int print_ed_scn(const struct opal_ed_scn *ed, void *cookie)
{
	print_header("Extended User Defined Data");
	print_opal_v6_hdr(ed->v6hdr);
	print_line("Created by", "%s", get_creator_name(ed->creator_id));
	print_hex(ed->user_data, ed->v6hdr.length - 12);
	return 0;
}
