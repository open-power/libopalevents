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

#include <stdlib.h>

#include <errno.h>
#include <string.h>

#include "opal-event-log.h"

opal_event_log *create_opal_event_log(void) {
	opal_event_log *log = malloc(sizeof(struct opal_event_log));
	if (!log)
		return NULL;

	bzero(log, sizeof(struct opal_event_log));

	return log;
}

int add_opal_event_log_scn(opal_event_log *log, void *scn,
                           enum opal_event_log_err *r_status) {
	if (!log)
		return -EINVAL;

	struct opal_event_log_scn *new = malloc(sizeof(struct opal_event_log_scn));

	if (!new)
		return -ENOMEM;

	struct opal_v6_hdr *hdr = (struct opal_v6_hdr *) scn;
	new->next = NULL;
	new->scn = scn;
	/* Relies on the fact that the v6 header is at the start of all sections */
	new->hdr = hdr;

	/* Check types and assign them to shortcut pointers */
	if (IS_SCN(hdr->id, "PH") && (!(log->p_hdr)))
		log->p_hdr = (struct opal_priv_hdr_scn *)scn;

	if (IS_SCN(hdr->id, "UH") && (!(log->u_hdr)))
		log->u_hdr = (struct opal_usr_hdr_scn *)scn;

	if(IS_SCN(hdr->id, "PS") && (!(log->p_src)))
		log->p_src = (struct opal_src_scn *)scn;

	if (IS_SCN(hdr->id, "EH") && (!(log->eh)))
		log->eh = (struct opal_eh_scn *)scn;

	if(IS_SCN(hdr->id, "MT") && (!(log->mtms)))
		log->mtms = (struct opal_mtms_scn *)scn;

	if (!log->tail) {
		log->tail = new;
	} else {
		log->tail->next = new;
		log->tail = new;
	}

	if (!log->scns)
		log->scns = new;

	if (r_status)
		*r_status = validate_opal_event_log(log);
	return 0;
}

int do_opal_event_log(opal_event_log *log, int (*func)(void *scn, void *cookie),
                      void *cookie)
{
	if (!log || !func)
		return -EINVAL;

	int count = 0;
	struct opal_event_log_scn *e = log->scns;
	while (e) {
		if (func(e->scn, cookie) == 0)
			count++;
		e = e->next;
	}

	return count;
}

int count_opal_event_log(opal_event_log *log) {
	if (!log)
		return -EINVAL;

	int count = 0;
	struct opal_event_log_scn *e = log->scns;
	while(e) {
		count++;
		e = e->next;
	}
	return count;
}

enum opal_event_log_err validate_opal_event_log(opal_event_log *log)
{
	if(!log)
		return OPAL_EVENT_LOG_NULL;

	int status = OPAL_EVENT_LOG_OK;

	/* Check to make sure all required sections are present */
	if(!(log->p_hdr) || (!(log->u_hdr)) || (!(log->eh)))
		status |= OPAL_EVENT_LOG_MISSING;

	/* These two must be present if log is an error */
	if(opal_event_log_is_error(log) && ((!(log->p_src)) || (!log->mtms)))
		status |= OPAL_EVENT_LOG_MISSING;

	int count = 0;
	struct opal_event_log_scn *i;
	struct opal_event_log_scn *e = log->scns;
	while (e) {
		count++;

		/* Check that the first three come in the correct order */
		if (count == 1 && !IS_SCN(e->hdr->id, "PH"))
			status |= OPAL_EVENT_LOG_ORDER;

		if (count == 2 && !IS_SCN(e->hdr->id, "UH"))
			status |= OPAL_EVENT_LOG_ORDER;

		if (count == 3 && !IS_SCN(e->hdr->id, "PS")
		    && opal_event_log_is_error(log))
			status |= OPAL_EVENT_LOG_ORDER;

		if (!(e->next) && e != log->tail)
			status |= OPAL_EVENT_LOG_ERR;

		/* Check that sections don't appear twice,
		 * don't bother searching for the onces which can appear
		 * multiple times */
		i = e->next;
		while (i && !IS_SCN(e->hdr->id, "SS")
			      && !IS_SCN(e->hdr->id, "SW")
			      && !IS_SCN(e->hdr->id, "UD")) {
			if (IS_SCN(e->hdr->id,i->hdr->id))
				status |= OPAL_EVENT_LOG_DUP;
			i = i->next;
		}
		e = e->next;
	}

	if (!(log->p_hdr)	|| count != log->p_hdr->scn_count)
		status |= OPAL_EVENT_LOG_COUNT;

	return status;
}

uint32_t opal_event_log_id(opal_event_log *log)
{
	if(!log || !(log->p_hdr))
		return 0;

	return log->p_hdr->log_entry_id;
}

int opal_event_log_is_error(opal_event_log *log)
{
	if(!log || !(log->u_hdr))
		return 0;

	return log->u_hdr->event_severity;
}

void *get_opal_event_log_scn(opal_event_log *log, const char *id, int n) {
	if (!log || !id || n < 0)
		return NULL;

	struct opal_event_log_scn *e = log->scns;
	while (e) {
		if (IS_SCN(e->hdr->id, id) && n-- == 0)
			return e->scn;
		e = e->next;
	}

	return NULL;
}

void *get_nth_opal_event_log_scn(opal_event_log *log, int n)
{
	if (!log || n < 0)
		return NULL;

	struct opal_event_log_scn *e = log->scns;
	while (e) {
		if(n-- == 0)
			return e->scn;
		e = e->next;
	}

	return NULL;
}

int free_opal_event_log(opal_event_log *log) {
	if (!log)
		return -EINVAL;

	struct opal_event_log_scn *t;
	struct opal_event_log_scn *e = log->scns;
	while (e) {
		t = e->next;
		free(e->scn);
		free(e);
		e = t;
	}

	return 0;
}
