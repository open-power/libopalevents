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
#include <stdarg.h>
#include <ctype.h>
#include <assert.h>

#include "parse-opal-event.h"

#include "print-opal-event.h"
#include "opal-event-data.h"
#include "parse_helpers.h"

int parse_opal_event_log(char *buf, int buflen, struct opal_event_log *log)
{
	if (!log || !buf)
		return -EINVAL;

	int rc;
	int tmp_rc;
	struct opal_v6_hdr hdr;
	struct opal_priv_hdr_scn *ph;
	int nrsections = 0;
	enum opal_event_log_err elog_errs;

	while (buflen) {
		rc = parse_section_header(&hdr, buf, buflen);
		if (rc < 0) {
			fprintf(stderr, "ERROR %s: Could not parse section header, giving up\n", __func__);
			break;
		}

		nrsections++;

		if (nrsections == 1) {
			tmp_rc = parse_priv_hdr_scn(&ph, &hdr, buf, buflen);
			if (tmp_rc == 0) {
				tmp_rc = add_opal_event_log(log, ph);
			} else {
				/* We didn't parse the private header, must stop */
				fprintf(stderr, "ERROR %s: Unable to parse private header section"
						" cannot continue\n", __func__);
				return -EINVAL;
			}
		} else if (IS_SCN(hdr.id, "UH")) {
			struct opal_usr_hdr_scn *usr;
			tmp_rc = parse_usr_hdr_scn(&usr, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, usr);
		} else if (IS_SCN(hdr.id, "PS") || IS_SCN(hdr.id, "SS")) {
			struct opal_src_scn *src;
			tmp_rc = parse_src_scn(&src, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, src);
		} else if (IS_SCN(hdr.id, "EH")) {
			struct opal_eh_scn *eh;
			tmp_rc = parse_eh_scn(&eh, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, eh);
		} else if (IS_SCN(hdr.id, "MT")) {
			struct opal_mtms_scn *mtms;
			tmp_rc = parse_mtms_scn(&mtms, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, mtms);
		} else if (IS_SCN(hdr.id, "DH")) {
			struct opal_dh_scn *dh;
			tmp_rc = parse_dh_scn(&dh, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, dh);
		} else if (IS_SCN(hdr.id, "SW")) {
			struct opal_sw_scn *sw;
			tmp_rc = parse_sw_scn(&sw, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, sw);
		} else if (IS_SCN(hdr.id, "LP")) {
			struct opal_lp_scn *lp;
			tmp_rc = parse_lp_scn(&lp, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, lp);
		} else if (IS_SCN(hdr.id, "LR")) {
			struct opal_lr_scn *lr;
			tmp_rc = parse_lr_scn(&lr, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, lr);
		} else if (IS_SCN(hdr.id, "HM")) {
			struct opal_hm_scn *hm;
			tmp_rc = parse_hm_scn(&hm, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, hm);
		} else if (IS_SCN(hdr.id, "EP")) {
			struct opal_ep_scn *ep;
			tmp_rc = parse_ep_scn(&ep, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, ep);
		} else if (IS_SCN(hdr.id, "IE")) {
			struct opal_ie_scn *ie;
			tmp_rc = parse_ie_scn(&ie, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, ie);
		} else if (IS_SCN(hdr.id, "MI")) {
			struct opal_mi_scn *mi;
			tmp_rc = parse_mi_scn(&mi, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, mi);
		} else if (IS_SCN(hdr.id, "CH")) {
			struct opal_ch_scn *ch;
			tmp_rc = parse_ch_scn(&ch, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, ch);
		} else if (IS_SCN(hdr.id, "UD")) {
			struct opal_ud_scn *ud;
			tmp_rc = parse_ud_scn(&ud, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, ud);
		} else if (IS_SCN(hdr.id, "EI")) {
			struct opal_ei_scn *ei;
			tmp_rc = parse_ei_scn(&ei, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, ei);
		} else if (IS_SCN(hdr.id, "ED")) {
			struct opal_ed_scn *ed;
			tmp_rc = parse_ed_scn(&ed, &hdr, buf, buflen);
			if (tmp_rc == 0)
				tmp_rc = add_opal_event_log(log, ed);
		}

		rc = (rc) ? rc : tmp_rc;

		buf += hdr.length;

		/* Do some validation on the event log
		 * It doesn't need to be perfect but some errors we will need to know
		 */

		elog_errs = validate_opal_event_log(log);
		if (elog_errs == OPAL_EVENT_LOG_ERR) {
			fprintf(stderr, "ERROR %s: Opal event log structure corruption detected"
			        " cannot continue\n", __func__);
			rc = -EINVAL;
			break;
		}

		if (nrsections == ph->scn_count)
			break;

	}

	/* Dont bother to do checks on the elog structure if an error was already
	 * detected */
	if (rc == 0) {
		elog_errs = validate_opal_event_log(log);
		rc = (elog_errs != OPAL_EVENT_LOG_OK) ? elog_errs : 0;
		if (elog_errs & OPAL_EVENT_LOG_MISSING)
			fprintf(stderr, "Warning %s: detected missing section in opal event log\n", __func__);

		if (elog_errs & OPAL_EVENT_LOG_ORDER)
			fprintf(stderr, "Warning %s: detected opal event log sections out of order\n", __func__);

		if (elog_errs & OPAL_EVENT_LOG_DUP)
			fprintf(stderr, "Warning %s: detected duplicate opal event log sections\n", __func__);

		if (elog_errs & OPAL_EVENT_LOG_COUNT)
			fprintf(stderr, "Warning %s: detected mismatch in number of opal event log sections\n", __func__);
	}
	return rc;
}

/* parse all required sections of the log */
int parse_opal_event(char *buf, int buflen)
{
	int rc;
	opal_event_log *log = create_opal_event_log();
	if (!log)
		return -ENOMEM;

	rc = parse_opal_event_log(buf, buflen, log);

	if (rc == 0)
		print_opal_event_log(log);

	free_opal_event_log(log);

	return rc;
}
