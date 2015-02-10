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

#ifndef _H_OPAL_SRC_FRU_SCN
#define _H_OPAL_SRC_FRU_SCN

#include <inttypes.h>

#include "opal-mtms-scn.h"

struct opal_fru_hdr {
	uint16_t type;
	uint8_t length;
	uint8_t flags;
} __attribute__((packed));


#define OPAL_FRU_ID_TYPE 0x4944 /* 'ID' in hex */

#define OPAL_FRU_ID_PART 0x08
#define OPAL_FRU_ID_PROC 0x02
#define OPAL_FRU_ID_PART_MAX 8

#define OPAL_FRU_ID_CCIN 0x04 /* OPAL_FRU_ID_PART must be set */
#define OPAL_FRU_ID_CCIN_MAX 4

#define OPAL_FRU_ID_SERIAL_MAX 12
#define OPAL_FRU_ID_SERIAL 0x1 /* OPAL_FRU_ID_PART must be set */

struct opal_fru_id_sub_scn {
	struct opal_fru_hdr hdr;
	char part[OPAL_FRU_ID_PART_MAX];
	char ccin[OPAL_FRU_ID_CCIN_MAX];
	char serial[OPAL_FRU_ID_SERIAL_MAX]; /* not null terminated */
} __attribute__((packed));


#define OPAL_FRU_MR_TYPE 0x4d52 /* 'MR" in hex */

#define OPAL_FRU_MR_MRU_MAX 15

struct opal_fru_mr_mru_scn {
	uint8_t reserved0;
	uint8_t reserved1;
	uint8_t reserved2;
	uint8_t priority;
	uint32_t id;
} __attribute__((packed));

struct opal_fru_mr_sub_scn {
	struct opal_fru_hdr hdr;
	uint32_t reserved;
	struct opal_fru_mr_mru_scn mru[OPAL_FRU_MR_MRU_MAX]; /* Max 15 */
} __attribute__((packed));


#define OPAL_FRU_PE_TYPE 0x5045 /* 'PE' in hex */

#define OPAL_FRU_PE_PCE_MAX 32

struct opal_fru_pe_sub_scn {
	struct opal_fru_hdr hdr;
	struct opal_mtms_struct mtms;
	char pce[OPAL_FRU_PE_PCE_MAX];
} __attribute__((packed));


#define OPAL_FRU_SCN_STATIC_SIZE (4 * sizeof(uint8_t))
#define OPAL_FRU_SCN_ID 0xc0

#define OPAL_FRU_LOC_CODE_MAX 80

#define OPAL_FRU_ID_SUB 0x08

#define OPAL_FRU_PE_SUB 0x03

#define OPAL_FRU_MR_SUB 0x04

struct opal_fru_scn {
	uint8_t length; /* Length of everything below including this */
	uint8_t type;
	uint8_t priority;
	uint8_t loc_code_len; /* Must be a multiple of 4 */
	char location_code[OPAL_FRU_LOC_CODE_MAX]; /* Variable length indicated my loc_code_len max 80 */
	struct opal_fru_id_sub_scn id; /* Optional */
	struct opal_fru_pe_sub_scn pe; /* Optional */
	struct opal_fru_mr_sub_scn mr; /* Optional */
} __attribute__((packed));

int parse_fru_scn(struct opal_fru_scn *fru_scn, const char *buf,
                  int buflen);

int print_fru_scn(const struct opal_fru_scn fru);

#endif /* _H_OPAL_SRC_FRU_SCN */
