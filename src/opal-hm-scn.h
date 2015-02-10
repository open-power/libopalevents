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

#ifndef _H_OPAL_HM_SCN
#define _H_OPAL_HM_SCN

#include "opal-v6-hdr.h"
#include "opal-mtms-struct.h"

struct opal_hm_scn {
	struct opal_v6_hdr v6hdr;
	struct opal_mtms_struct mtms;
} __attribute__((packed));

int parse_hm_scn(struct opal_hm_scn **r_hm,
                 const struct opal_v6_hdr *hdr,
                 const char *buf, int buflen);

int print_hm_scn(const struct opal_hm_scn *hm, void *cookie);

#endif /* _H_OPAL_HM_SCN */
