/*
 * $QNXLicenseC:
 * Copyright 2020, 2023, BlackBerry Limited.
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

#include "externs.h"

unsigned
options(int argc, char *argv[])
{
    int             opt;
    int             numports = 0;
    void            *link;

    static TTYINIT devinit = {
        .port = 0,
        .port_shift = 0,
        .intr = 0,
        .baud = 115200,
        .isize = 2048,
        .osize = 2048,
        .csize = 256,
        .c_cflag = 0,
        .c_iflag = 0,
        .c_lflag = 0,
        .c_oflag = 0,
        .fifo = 0xe8,
        .clk = 500000000,
        .div = 541,
        .name = "/dev/ser",
        .reserved1 = NULL,
        .reserved2 = 0,
        .verbose = 0,
        .highwater = 0,
        .logging_path = "",
        .lflags = 0,
        .unit = 1
    };

    /*
     * Initialize the devinit to raw mode
     */
    ttc(TTC_INIT_RAW, &devinit, 0);

    while (optind < argc) {
        /*
         * Process dash options.
         */
        while ((opt = getopt(argc, argv, IO_CHAR_SERIAL_OPTIONS "")) != -1) {
            switch (ttc(TTC_SET_OPTION, &devinit, opt)) {
                default:
                    break;
            }
        }

        /*
         * Process ports and interrupts.
         */
        while (optind < argc  &&  *(optarg = argv[optind]) != '-') {
            devinit.port = strtoul(optarg, &optarg, 16);
            if (*optarg == ',')
                devinit.intr = strtoul(optarg + 1, NULL, 0);
            create_device(&devinit);
            devinit.unit++;
            ++numports;
            ++optind;
        }
    }

    return numports;
}

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/hardware/branches/release/hardware/devc/serminiuart/options.c $ $Rev: 987527 $")
#endif
