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

#ifndef _H_OPAL_EVENTS
#define _H_OPAL_EVENTS

#include <inttypes.h>

enum opal_event_log_flags {
	OPAL_EVENT_ALL = 0,
	OPAL_EVENT_ACTION = 1, /* Mutally exclusive */
	OPAL_EVENT_HEALTH = 2, /* Mutally exclusive */
	OPAL_EVENT_REPORT_ALL = 4,
	OPAL_EVENT_REPORT_HMC = 8,
	OPAL_EVENT_CALL_HOME = 16
};

typedef struct opal_event_log opal_event;

typedef enum opal_event_log_flags opal_event_flags;

opal_event *opal_event_create(void);

int opal_event_parse(opal_event *event, char *buf, int buflen);

int opal_event_print(opal_event *event);

int opal_event_summarise_hdr(void);

int opal_event_summarise(opal_event *event, opal_event_flags flags);

uint32_t opal_event_get_logid(opal_event *event);

int opal_event_destroy(opal_event *event);

#endif /* _H_OPAL_EVENTS */
