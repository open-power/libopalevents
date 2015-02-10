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

#ifndef _H_OPAL_MTMS_STRUCT
#define _H_OPAL_MTMS_STRUCT

#include <string.h>

#define OPAL_SYS_MODEL_LEN  8
#define OPAL_SYS_SERIAL_LEN 12

struct opal_mtms_struct {
	char model[OPAL_SYS_MODEL_LEN];
	char serial_no[OPAL_SYS_SERIAL_LEN];
} __attribute__((packed));

static inline void copy_mtms_struct(struct opal_mtms_struct *dest,
                             const struct opal_mtms_struct *src)
{
	memcpy(dest->model, src->model, OPAL_SYS_MODEL_LEN);
	memcpy(dest->serial_no, src->serial_no, OPAL_SYS_SERIAL_LEN);
}

int print_mtms_struct(const struct opal_mtms_struct mtms);

#endif /* _H_OPAL_MTMS_STRUCT */
