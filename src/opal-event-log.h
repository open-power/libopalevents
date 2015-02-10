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

#ifndef _H_OPAL_EVENT_LOG
#define _H_OPAL_EVENT_LOG

#include <stdlib.h>
#include "opal-v6-hdr.h"
#include "opal-priv-hdr-scn.h"
#include "opal-usr-scn.h"

#define IS_SCN(hdr_id,id) (strncmp(hdr_id, id, 2) == 0)

/** OPAL Event Log Error Codes */
enum opal_event_log_err {
	OPAL_EVENT_LOG_OK =       0,
	OPAL_EVENT_LOG_ERR =      1,
	OPAL_EVENT_LOG_DUP =      2,
	OPAL_EVENT_LOG_COUNT =    4,
	OPAL_EVENT_LOG_NULL  =    8,
	OPAL_EVENT_LOG_MISSING = 16,
	OPAL_EVENT_LOG_ORDER =   32
};

struct opal_event_log_scn {
	struct opal_v6_hdr *hdr;
	void *scn;
	struct opal_event_log_scn *next;
};

struct opal_event_log {
	/* These sections may be required
	 * Keep pointers to them to speed access
	 */
	struct opal_priv_hdr_scn *p_hdr;
	struct opal_usr_hdr_scn *u_hdr;
	struct opal_src_scn *p_src;
	struct opal_eh_scn *eh;
	struct opal_mtms_scn *mtms;

	/* All sections in order */
	struct opal_event_log_scn *scns;
	struct opal_event_log_scn *tail;
};

typedef struct opal_event_log opal_event_log;

opal_event_log *create_opal_event_log(void);

int add_opal_event_log_scn(opal_event_log *log, void *scn,
                           enum opal_event_log_err *r_status);

void *get_opal_event_log_scn(opal_event_log *log, const char *id, int n);

static inline int add_opal_event_log(opal_event_log *log, void *scn) {
	return add_opal_event_log_scn(log, scn, NULL);
}

void *get_opal_event_log_scn(opal_event_log *log, const char *id, int n);

int count_opal_event_log(opal_event_log *log);

int do_opal_event_log(opal_event_log *log,
                      int (*func)(void *scn, void *cookie), void *cookie);

uint32_t opal_event_log_id(opal_event_log *log);

enum opal_event_log_err validate_opal_event_log(opal_event_log *log);

int opal_event_log_is_error(opal_event_log *log);

int free_opal_event_log(opal_event_log *log);


__attribute__ ((unused))
static struct opal_priv_hdr_scn *get_priv_hdr_scn(opal_event_log *log) {
	return (struct opal_priv_hdr_scn *) get_opal_event_log_scn(log, "PH", 0);
}

__attribute__ ((unused))
static struct opal_usr_hdr_scn *get_usr_hdr_scn(opal_event_log *log) {
	return (struct opal_usr_hdr_scn *) get_opal_event_log_scn(log, "UH", 0);
}

__attribute__ ((unused))
static struct opal_src_scn *get_src_ps_scn(opal_event_log *log) {
	return (struct opal_src_scn *) get_opal_event_log_scn(log, "PS", 0);
}

__attribute__ ((unused))
static struct opal_eh_scn *get_eh_scn(opal_event_log *log) {
	return (struct opal_eh_scn *) get_opal_event_log_scn(log, "EH", 0);
}

__attribute__ ((unused))
static struct opal_mtms_scn *get_mtms_scn(opal_event_log *log) {
	return (struct opal_mtms_scn *) get_opal_event_log_scn(log, "MT", 0);
}

__attribute__ ((unused))
static struct opal_src_scn *get_src_ss_scn(opal_event_log *log, int n) {
	return (struct opal_src_scn *) get_opal_event_log_scn(log, "SS", n);
}

__attribute__ ((unused))
static struct opal_dh_scn *get_dh_scn(opal_event_log *log) {
	return (struct opal_dh_scn *) get_opal_event_log_scn(log, "DH", 0);
}

__attribute__ ((unused))
static struct opal_sw_scn *get_sw_scn(opal_event_log *log, int n) {
	return (struct opal_sw_scn *) get_opal_event_log_scn(log, "SW", n);
}

__attribute__ ((unused))
static struct opal_lp_scn *get_lp_scn(opal_event_log *log) {
	return (struct opal_lp_scn *) get_opal_event_log_scn(log, "LP", 0);
}

__attribute__ ((unused))
static struct opal_lr_scn *get_lr_scn(opal_event_log *log) {
	return (struct opal_lr_scn *) get_opal_event_log_scn(log, "LR", 0);
}

__attribute__ ((unused))
static struct opal_ep_scn *get_ep_scn(opal_event_log *log) {
	return (struct opal_ep_scn *) get_opal_event_log_scn(log, "EP", 0);
}

__attribute__ ((unused))
static struct opal_ie_scn *get_ie_scn(opal_event_log *log) {
	return (struct opal_ie_scn *) get_opal_event_log_scn(log, "IE", 0);
}

__attribute__ ((unused))
static struct opal_mi_scn *get_mi_scn(opal_event_log *log) {
	return (struct opal_mi_scn *) get_opal_event_log_scn(log, "MI", 0);
}

__attribute__ ((unused))
static struct opal_ch_scn *get_ch_scn(opal_event_log *log) {
	return (struct opal_ch_scn *) get_opal_event_log_scn(log, "CH", 0);
}

__attribute__ ((unused))
static struct opal_ud_scn *get_ud_scn(opal_event_log *log, int n) {
	return (struct opal_ud_scn *) get_opal_event_log_scn(log, "UD", n);
}

__attribute__ ((unused))
static struct opal_ei_scn *get_ei_scn(opal_event_log *log) {
	return (struct opal_ei_scn *) get_opal_event_log_scn(log, "EI", 0);
}

__attribute__ ((unused))
static struct opal_ed_scn *get_ed_scn(opal_event_log *log, int n) {
	return (struct opal_ed_scn *) get_opal_event_log_scn(log, "ED", n);
}

#endif /* _H_OPAL_EVENT_LOG */
