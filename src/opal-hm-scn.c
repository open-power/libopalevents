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

#include "opal-hm-scn.h"
#include "print_helpers.h"

int parse_hm_scn(struct opal_hm_scn **r_hm,
                 const struct opal_v6_hdr *hdr,
                 const char *buf, int buflen)
{
	struct opal_hm_scn *bufhm = (struct opal_hm_scn *)buf;
	struct opal_hm_scn *hm;
	if (buflen < sizeof(struct opal_hm_scn)) {
		fprintf(stderr, "%s: corrupted, expected length >= %lu, got %u\n",
			__func__,
			sizeof(struct opal_hm_scn), buflen);
		return -EINVAL;
	}

	*r_hm = malloc(sizeof(struct opal_hm_scn));
	if(!*r_hm)
		return -ENOMEM;
	hm = *r_hm;

	hm->v6hdr = *hdr;
	copy_mtms_struct(&(hm->mtms), &(bufhm->mtms));

	return 0;
}

int print_hm_scn(const struct opal_hm_scn *hm, void *cookie)
{
	print_header("Hypervisor ID");

	print_opal_v6_hdr(hm->v6hdr);
	print_mtms_struct(hm->mtms);

	return 0;
}
