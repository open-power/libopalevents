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
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <inttypes.h>

#include "libopalevents-1.0/libopalevents.h"
#include "opal-event-log.h"
#include "parse-opal-event.h"
#include "print-opal-event.h"

opal_event *opal_event_create(void)
{
	return create_opal_event_log();
}

int opal_event_parse(opal_event *event, char *buf, int buflen)
{
	return parse_opal_event_log(buf, buflen, event);
}

int opal_event_print(opal_event *event)
{
	return print_opal_event_log(event);
}

int opal_event_summarise_hdr(void)
{
	return header_opal_event_log();
}

int opal_event_summarise(opal_event *event, opal_event_flags flags)
{
	return summarise_opal_event_log(event, flags);
}

uint32_t opal_event_get_logid(opal_event *event)
{
	return opal_event_log_id(event);
}

int opal_event_destroy(opal_event *event)
{
	return free_opal_event_log(event);
}
