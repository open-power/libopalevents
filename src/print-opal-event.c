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
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "print-opal-event.h"

#include "print_helpers.h"
#include "opal-event-data.h"
#include "opal-event-log.h"
#include "opal-src-scn.h"

int print_opal_event_log_cb(void *scn, void *cookie)
{
	struct opal_v6_hdr *hdr = (struct opal_v6_hdr *)scn;
	int rc = -EINVAL;
	if (IS_SCN(hdr->id, "PH")) {
		rc = print_priv_hdr_scn((const struct opal_priv_hdr_scn *)scn,
		                        cookie);
	} else if (IS_SCN(hdr->id, "UH")) {
		rc = print_usr_hdr_scn((const struct opal_usr_hdr_scn *)scn,
		                       cookie);
	} else if (IS_SCN(hdr->id, "PS")) {
		rc = print_src_scn((const struct opal_src_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "EH")) {
		rc = print_eh_scn((const struct opal_eh_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "MT")) {
		rc = print_mtms_scn((const struct opal_mtms_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "SS")) {
		rc = print_src_scn((const struct opal_src_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "DH")) {
		rc = print_dh_scn((const struct opal_dh_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "SW")) {
		rc = print_sw_scn((const struct opal_sw_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "LP")) {
		rc = print_lp_scn((const struct opal_lp_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "LR")) {
		rc = print_lr_scn((const struct opal_lr_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "HM")) {
		rc = print_hm_scn((const struct opal_hm_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "EP")) {
		rc = print_ep_scn((const struct opal_ep_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "IE")) {
		rc = print_ie_scn((const struct opal_ie_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "MI")) {
		rc = print_mi_scn((const struct opal_mi_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "CH")) {
		rc = print_ch_scn((const struct opal_ch_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "UD")) {
		rc = print_ud_scn((const struct opal_ud_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "EI")) {
		rc = print_ei_scn((const struct opal_ei_scn *)scn, cookie);
	} else if (IS_SCN(hdr->id, "ED")) {
		rc = print_ed_scn((const struct opal_ed_scn *)scn, cookie);
	}

	return rc;
}

int print_opal_event_log(opal_event_log *log)
{
	if (!log)
		return -1;

	int count = do_opal_event_log(log, print_opal_event_log_cb, NULL);
	int total = count_opal_event_log(log);
	if (total < 0 || total != count)
		return -1;

	return 0;
}

static int test_flags(enum opal_event_log_flags flags, uint16_t action)
{
	if ((flags & OPAL_EVENT_ACTION) && !(action & OPAL_UH_ACTION_SERVICE))
		return 0;

	if ((flags & OPAL_EVENT_HEALTH) && !(action & OPAL_UH_ACTION_HEALTH))
		return 0;

	if ((flags & OPAL_EVENT_REPORT_ALL) && !(action & OPAL_UH_ACTION_REPORT_EXTERNALLY))
		return 0;

	if ((flags & OPAL_EVENT_REPORT_HMC) && !(action & OPAL_UH_ACTION_HMC_ONLY))
		return 0;

	if ((flags & OPAL_EVENT_CALL_HOME) && !(action & OPAL_UH_ACTION_CALL_HOME))
		return 0;

	return 1;
}

int header_opal_event_log(void)
{
	return print_header("ID       Date       Time     SRC        Creator           Event Severity      ");
}

int summarise_opal_event_log(opal_event_log *log, enum opal_event_log_flags flags)
{
	if (!log)
		return -1;

	if ((flags & (EX_EVENT_LOG_FLAGS)) == EX_EVENT_LOG_FLAGS)
		return -1;

	char c;
	const char *desc = "?UNKNOWN";
	uint16_t act = 0;
	struct opal_datetime date_time_out;
	char prefcode[9] = "?UNKNOWN";
	const struct opal_priv_hdr_scn *privhdr = (const struct opal_priv_hdr_scn *) get_priv_hdr_scn(log);
	const struct opal_usr_hdr_scn *usrhdr = (const struct opal_usr_hdr_scn *) get_usr_hdr_scn(log);
	const struct opal_src_scn *psrc = (const struct opal_src_scn *) get_src_ps_scn(log);
	if(!privhdr)
		return -1;

	/* This function tries to be as robust as possible
	 * even if usrhdr and psrc weren't parsed, try to
	 * print something meaningful anyway
	 */
	date_time_out = privhdr->commit_datetime;
	if (psrc)
		memcpy(prefcode, psrc->primary_refcode, 8);

	if (usrhdr) {
		act = usrhdr->action;
		desc = get_severity_desc(usrhdr->event_severity & 0xF0);
	}

	if (test_flags(flags, act)) {
		c = '?';
		if (usrhdr)
			c = ' ';
		if ((flags == OPAL_EVENT_ALL) && (act & OPAL_UH_ACTION_SERVICE))
			c = '+';

		printf("|%08X %04u-%02u-%02u %02u:%02u:%02u %8.8s %c %-17.17s %-20.20s|\n",
		       privhdr->log_entry_id, date_time_out.year, date_time_out.month, date_time_out.day,
		       date_time_out.hour, date_time_out.minutes, date_time_out.seconds, prefcode,
		       c, get_creator_name(privhdr->creator_id), desc);
	}

	return 0;
}
