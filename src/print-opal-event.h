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

#ifndef _H_OPAL_PRINT_EVENT
#define _H_OPAL_PRINT_EVENT

#include "libopalevents-1.0/libopalevents.h"
#include "opal-event-data.h"
#include "opal-event-log.h"

#define EX_EVENT_LOG_FLAGS (OPAL_EVENT_ACTION | OPAL_EVENT_HEALTH)

int print_opal_event_log(opal_event_log *log);

int header_opal_event_log(void);

int summarise_opal_event_log(opal_event_log *log, enum opal_event_log_flags flags);

int get_field_desc(
		struct generic_desc *data,
		int length,
		int id,
		int default_id,
		int default_index);

#endif /* _H_OPAL_PRINT_EVENT */
