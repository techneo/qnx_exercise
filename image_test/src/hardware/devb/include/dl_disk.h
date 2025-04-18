/*
 * $QNXLicenseC: 
 * Copyright 2008, QNX Software Systems.  
 *  
 * Licensed under the Apache License, Version 2.0 (the "License"). You  
 * may not reproduce, modify or distribute this software except in  
 * compliance with the License. You may obtain a copy of the License  
 * at: http://www.apache.org/licenses/LICENSE-2.0  
 *  
 * Unless required by applicable law or agreed to in writing, software  
 * distributed under the License is distributed on an "AS IS" basis,  
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied. 
 * 
 * This file may contain contributions from others, either as  
 * contributors under the License or as licensors under other terms.   
 * Please review this entire file for other proprietary rights or license  
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */
#ifndef DL_DISK_H_INCLUDED
#define DL_DISK_H_INCLUDED

#include <ntocam.h>

extern int dll_pdrvr_init_disk( cam_entry_t *cam_funcs, char *argv[] );
extern int cam_pdrv_version_disk;

/*
 * This list is matched with the exported symbol list.
 */
static const struct dll_syms disk_syms[] = {
	{ .symname = "dll_pdrvr_init", .addr  = &dll_pdrvr_init_disk },
	{ .symname = "cam_pdrv_version", .addr  = &cam_pdrv_version_disk },
	{ .symname = NULL, .addr  = NULL }
};

/*
 * This matched the dll file name
 */
#define CAM_DISK_LIST		{ .fname = "cam-disk.so", .syms = disk_syms }
#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/hardware/branches/release/hardware/devb/include/dl_disk.h $ $Rev: 982571 $")
#endif
