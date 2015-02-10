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

#include "opal-usr-scn.h"
#include "opal-event-data.h"
#include "print_helpers.h"

int parse_usr_hdr_scn(struct opal_usr_hdr_scn **r_usrhdr,
                      const struct opal_v6_hdr *hdr,
                      const char *buf, int buflen)
{
	struct opal_usr_hdr_scn *bufhdr = (struct opal_usr_hdr_scn*)buf;
	struct opal_usr_hdr_scn *usrhdr;

	if (buflen < sizeof(struct opal_usr_hdr_scn)) {
		fprintf(stderr, "%s: corrupted, expected length %lu, got %u\n",
		        __func__, sizeof(struct opal_usr_hdr_scn), buflen);
		return -EINVAL;
	}

	if (hdr->length != sizeof(struct opal_usr_hdr_scn)) {
		fprintf(stderr, "%s: section header length disagrees with spec"
		        ". section header length %u, spec: %lu\n", __func__,
		        hdr->length, sizeof(struct opal_usr_hdr_scn));
		return -EINVAL;
	}

	*r_usrhdr = malloc(sizeof(struct opal_usr_hdr_scn));
	if(!*r_usrhdr)
		return -ENOMEM;
	usrhdr = *r_usrhdr;

	usrhdr->v6hdr = *hdr;
	usrhdr->subsystem_id = bufhdr->subsystem_id;
	usrhdr->event_data = bufhdr->event_data;
	usrhdr->event_severity = bufhdr->event_severity;
	usrhdr->event_type = bufhdr->event_type;
	usrhdr->problem_domain = bufhdr->problem_domain;
	usrhdr->problem_vector = bufhdr->problem_vector;
	usrhdr->action = be16toh(bufhdr->action);

	return 0;
}

int print_usr_hdr_scn(const struct opal_usr_hdr_scn *usrhdr, void *cookie)
{
	char *entry = "Action Flags";

	print_header("User Header");

	print_opal_v6_hdr(usrhdr->v6hdr);
	print_line("Subsystem", "%s", get_subsystem_name(usrhdr->subsystem_id));

	print_line("Event Scope", "%s", get_event_scope(usrhdr->event_data));

	print_line("Event Severity", "%s", get_severity_desc(usrhdr->event_severity));

	print_line("Event Type", "%s", get_event_desc(usrhdr->event_type));

	if (!(usrhdr->action & OPAL_UH_ACTION_HEALTH)) {
		if (usrhdr->action & OPAL_UH_ACTION_REPORT_EXTERNALLY) {
			if (usrhdr->action & OPAL_UH_ACTION_HMC_ONLY)
				print_line(entry,"Report to Hypervisor");
			else
				print_line(entry, "Report to Operating System");
				entry = "";
		}

		if (usrhdr->action & OPAL_UH_ACTION_SERVICE) {
			print_line(entry, "Service Action Required");
			if (usrhdr->action & OPAL_UH_ACTION_CALL_HOME)
				print_line("","Call Home");
			if(usrhdr->action & OPAL_UH_ACTION_TERMINATION)
				print_line("","Termination Error");
			entry = "";
		}

		if (usrhdr->action & OPAL_UH_ACTION_ISO_INCOMPLETE) {
			print_line(entry, "Error isolation incomplete");
			print_line("","Further analysis required");
			entry = "";
		}
	} else {
		print_line(entry, "Healthy System Event");
		print_line("", "No Service Action Required");
		entry = "";
	}

	if (entry[0] != '\0') {
		print_line(entry, "Unknown action flag (0x%08x)", usrhdr->action);
	}

	return 0;
}
