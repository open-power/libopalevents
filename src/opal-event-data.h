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

#ifndef _H_OPAL_EVENTS_DATA
#define _H_OPAL_EVENTS_DATA

#include <stdint.h>

struct generic_desc{
	uint8_t id;
	const char *desc;
};

const char *get_event_desc(uint8_t id);

const char *get_subsystem_name(uint8_t id);

const char *get_severity_desc(uint8_t id);

const char *get_creator_name(uint8_t id);

const char *get_event_scope(uint8_t id);

const char *get_elog_desc(uint8_t id);

const char *get_fru_priority_desc(uint8_t id);

const char *get_fru_component_desc(uint8_t id);

const char *get_ep_event_desc(uint8_t id);

const char *get_lr_res_desc(uint8_t id);

const char *get_ie_type_desc(uint8_t id);

const char *get_ie_scope_desc(uint8_t id);

const char *get_ie_subtype_desc(uint8_t id);

const char *get_dh_type_desc(uint8_t id);
#endif /* _H_OPAL_EVENTS_DATA */
