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
#include <string.h>
#include <errno.h>

#include "opal-mtms-scn.h"
#include "print_helpers.h"

int parse_mtms_scn(struct opal_mtms_scn **r_mtms, const struct opal_v6_hdr *hdr,
		const char *buf, int buflen) {

	struct opal_mtms_scn *bufmtms = (struct opal_mtms_scn*)buf;
	struct opal_mtms_scn *mtms;

	if (buflen < sizeof(struct opal_mtms_scn)) {
		fprintf(stderr, "%s: corrupted, expected length %lu, got %u\n",
		        __func__, sizeof(struct opal_mtms_scn), buflen);
		return -EINVAL; }

	if (hdr->length != sizeof(struct opal_mtms_scn)) {
		fprintf(stderr, "%s: section header length disagrees with spec"
		        ". section header length %u, spec: %lu\n",
		        __func__, hdr->length, sizeof(struct opal_mtms_scn));
		return -EINVAL;
	}

	*r_mtms = malloc(sizeof(struct opal_mtms_scn));
	if(!*r_mtms)
		return -ENOMEM;
	mtms = *r_mtms;

	mtms->v6hdr = *hdr;
	copy_mtms_struct(&(mtms->mtms), &(bufmtms->mtms));

	return 0;
}

int print_mtms_scn(const struct opal_mtms_scn *mtms, void *cookie)
{
	print_header("Machine Type/Model & Serial Number");
	print_opal_v6_hdr(mtms->v6hdr);
	print_mtms_struct(mtms->mtms);
	return 0;
}
