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

#include "opal-ie-scn.h"
#include "opal-event-data.h"
#include "print_helpers.h"

int parse_ie_scn(struct opal_ie_scn **r_ie,
                 struct opal_v6_hdr *hdr,
                 const char *buf, int buflen)
{
	struct opal_ie_scn *iebuf = (struct opal_ie_scn *)buf;
	struct opal_ie_scn *ie;

	if (buflen < sizeof(struct opal_ie_scn) - IE_DATA_MAX) {
		fprintf(stderr, "%s: corrupted, expected length => %lu, got %u\n",
		        __func__, sizeof(struct opal_ie_scn) - IE_DATA_MAX, buflen);
		return -EINVAL;
	}

	*r_ie = malloc(sizeof(struct opal_ie_scn));
	if (!*r_ie)
		return -ENOMEM;
	ie = *r_ie;

	ie->v6hdr = *hdr;
	ie->type = iebuf->type;
	ie->rpc_len = iebuf->rpc_len;
	ie->scope = iebuf->scope;
	ie->subtype = iebuf->subtype;
	ie->drc = be32toh(iebuf->drc);
	if (ie->type == IE_TYPE_RPC_PASS_THROUGH) {
		if (buflen < sizeof(struct opal_ie_scn) - IE_DATA_MAX + ie->rpc_len) {
			fprintf(stderr, "%s: corrupted, exptected length => %lu, got %u",
			        __func__, sizeof(struct opal_ie_scn) - IE_DATA_MAX +
			        ie->rpc_len, buflen);
			free(ie);
			return -EINVAL;
		}
		memcpy(ie->data.rpc, iebuf->data.rpc, ie->rpc_len);
	}
	if (ie->subtype == IE_SUBTYPE_PLAT_MAX_CHANGE) {
		if (buflen < sizeof(struct opal_ie_scn) - IE_DATA_MAX + sizeof(uint64_t)) {
			fprintf(stderr, "%s: corrupted, exptected length => %lu, got %u",
			        __func__, sizeof(struct opal_ie_scn) - IE_DATA_MAX +
			        sizeof(uint64_t), buflen);
			free(ie);
			return -EINVAL;
		}
		ie->data.max = be64toh(iebuf->data.max);
	}

	return 0;
}

int print_ie_scn(const struct opal_ie_scn *ie, void *cookie)
{
	print_header("IO Event");
	print_opal_v6_hdr(ie->v6hdr);
	print_line("Type", "%s", get_ie_type_desc(ie->type));
	print_line("DRC Index", "0x%08x", ie->drc);
	if (ie->type != IE_TYPE_EVENT) {
		print_line("Scope", "%s", get_ie_scope_desc(ie->scope));
		print_line("Sub Type", "%s", get_ie_subtype_desc(ie->subtype));
		if (ie->type == IE_TYPE_RPC_PASS_THROUGH) {
			print_line("RPC Length", "0x%02x", ie->rpc_len);
			print_center("RPC Data");
			print_hex(ie->data.rpc, ie->rpc_len);
		}

		if (ie->subtype == IE_SUBTYPE_PLAT_MAX_CHANGE)
			print_line("Change platform size to", "0x%016lx", ie->data.max);
	}

	return 0;
}

