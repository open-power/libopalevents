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

#include "opal-ch-scn.h"
#include "print_helpers.h"

/* Call Home Section */
int parse_ch_scn(struct opal_ch_scn **r_ch,
                 struct opal_v6_hdr *hdr,
                 const char *buf, int buflen)
{
	struct opal_ch_scn *ch;
	struct opal_ch_scn *bufch = (struct opal_ch_scn*)buf;

	*r_ch = malloc(hdr->length);
	if (!*r_ch)
		return -ENOMEM;
	ch = *r_ch;

	if (buflen < sizeof(struct opal_ch_scn)) {
		fprintf(stderr, "%s: corrupted, expected length >= %lu, got %u\n",
			__func__,
			sizeof(struct opal_ch_scn), buflen);
		free(ch);
		return -EINVAL;
	}

	if (hdr->length - sizeof(struct opal_v6_hdr) > OPAL_CH_COMMENT_MAX_LEN) {
		fprintf(stderr, "%s: corrupted, call home comment is longer than %u,"
			  " got %lu\n", __func__, OPAL_CH_COMMENT_MAX_LEN,
			  hdr->length - sizeof(struct opal_v6_hdr));
		free(ch);
		return -EINVAL;
	}

	ch->v6hdr = *hdr;

	strncpy(ch->comment, bufch->comment, hdr->length - sizeof(struct opal_v6_hdr));
	/* Make sure there is a null byte at the end */
	ch->comment[hdr->length - sizeof(struct opal_v6_hdr) - 1] = '\0';

	return 0;
}

int print_ch_scn(const struct opal_ch_scn *ch, void *cookie)
{
	print_header("Call Home Log Comment");
	print_opal_v6_hdr(ch->v6hdr);
	print_line("Call Home Comment", "%s", ch->comment);

	return 0;
}
