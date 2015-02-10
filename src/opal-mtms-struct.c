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

#include "opal-mtms-struct.h"
#include "print_helpers.h"

int print_mtms_struct(const struct opal_mtms_struct mtms)
{
	char model[OPAL_SYS_MODEL_LEN+1];
	char serial_no[OPAL_SYS_SERIAL_LEN+1];

	memcpy(model, mtms.model, OPAL_SYS_MODEL_LEN);
	model[OPAL_SYS_MODEL_LEN] = '\0';
	memcpy(serial_no, mtms.serial_no, OPAL_SYS_SERIAL_LEN);
	serial_no[OPAL_SYS_SERIAL_LEN] = '\0';

	print_line("Machine Type Model", "%s", model);
	print_line("Serial Number", "%s", serial_no);

	return 0;
}
