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

#include "opal-ep-scn.h"
#include "opal-event-data.h"
#include "print_helpers.h"

int parse_ep_scn(struct opal_ep_scn **r_ep,
                 const struct opal_v6_hdr *hdr,
                 const char *buf, int buflen)
{
	struct opal_ep_scn *bufep = (struct opal_ep_scn *)buf;
	struct opal_ep_scn *ep;

	if (buflen < sizeof(struct opal_ep_scn)) {
		fprintf(stderr, "%s: corrupted, expected length >= %lu, got %u\n",
		        __func__,
		        sizeof(struct opal_ep_scn), buflen);
		return -EINVAL;
	}

	*r_ep = malloc(sizeof(struct opal_ep_scn));
	if(!*r_ep)
		return -ENOMEM;
	ep = *r_ep;

	ep->v6hdr = *hdr;

	ep->value = bufep->value;
	ep->modifier = bufep->modifier;
	ep->ext_modifier = be16toh(bufep->ext_modifier);
	ep->reason = be32toh(bufep->reason);

	return 0;
}

int print_ep_scn(const struct opal_ep_scn *ep, void *cookie)
{
	print_header("EPOW");
	print_opal_v6_hdr(ep->v6hdr);
	print_line("Sensor Value", "0x%x", ep->value >> OPAL_EP_VALUE_SHIFT);
	print_line("EPOW Action", "0x%x", ep->value & OPAL_EP_ACTION_BITS);
	print_line("EPOW Event", "0x%x", ep->modifier >> OPAL_EP_EVENT_SHIFT);
	if ((ep->value >> OPAL_EP_VALUE_SHIFT) == OPAL_EP_VALUE_SET) {
		print_line("EPOW Event Modifier", "%s",
		           get_ep_event_desc(ep->modifier & OPAL_EP_EVENT_BITS));
		if (ep->v6hdr.version == OPAL_EP_HDR_V) {
			if (ep->ext_modifier == 0x00)
				print_line("EPOW Ext Modifier", "System wide shutdown");
			else if (ep->ext_modifier == 0x01)
				print_line("EPOW Ext Modifier", "Parition specific shutdown");
		}
	}
	print_line("Platform reason code", "0x%x", ep->reason);

	return 0;
}
