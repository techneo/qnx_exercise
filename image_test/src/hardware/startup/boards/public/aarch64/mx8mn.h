/*
 * $QNXLicenseC:
 * Copyright 2018-2019 NXP
 * Copyright 2020, QNX Software Systems.
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

#ifndef IMXMN_SOC_H_
#define IMXMN_SOC_H_


/*
 * AHB to IP Bridge Trust Zone (AIPSTZ)
 */
#define IMX_AIPS1_CONFIG_BASE                   0x301F0000
#define IMX_AIPS2_CONFIG_BASE                   0x305F0000
#define IMX_AIPS3_CONFIG_BASE                   0x309F0000
#define IMX_AIPS4_CONFIG_BASE                   0x32DF0000

/*
 * Boot information for software
 */
#define IMX_BOOT_INFORMATION_A0_BASE            0x000009E8
#define IMX_BOOT_INFORMATION_B0_BASE            0x00000968

/*
 * Clock Control Module (CCM)
 */
#define IMX_CCM_BASE                            0x30380000
#define IMX_CCM_SIZE                            0x10000

/*
 * Clock Control Module Analog part (CCM_ANALOG)
 */
#define IMX_CCM_ANALOG_BASE                     0x30360000
#define IMX_CCM_ANALOG_SIZE                     0x10000

/*
 * Central Security Unit (CSU)
 */
#define IMX_CSU_BASE                            0x303E0000
#define IMX_CSU_SIZE                            0x10000

/*
 * Ethernet MAC (ENET)
 */
#define IMX_ENET1_BASE                         0x30BE0000
#define IMX_ENET1_MEM_SIZE                     0x10000

#define IMX_ENET1_IRQ                          152

/*
 * Generic interrupt controller (GIC)
 */
#define IMX_GIC_GICD_BASE                      0x38800000   /* CPU distributor BASE address */
#define IMX_GIC_GICR_BASE                      0x38880000   /* CPU redistributor BASE address */
#define IMX_GIC_GICC_BASE                      0x52000000
/*
 * General Purpose Input/Output (GPIO)
 */
#define IMX_GPIO1_BASE                         0x30200000
#define IMX_GPIO2_BASE                         0x30210000
#define IMX_GPIO3_BASE                         0x30220000
#define IMX_GPIO4_BASE                         0x30230000
#define IMX_GPIO5_BASE                         0x30240000

#define IMX_GPIO_SIZE                          0x10000

#define IMX_GPIO1_LOW_IRQ                      96
#define IMX_GPIO1_HIGH_IRQ                     97
#define IMX_GPIO2_LOW_IRQ                      98
#define IMX_GPIO2_HIGH_IRQ                     99
#define IMX_GPIO3_LOW_IRQ                      100
#define IMX_GPIO3_HIGH_IRQ                     101
#define IMX_GPIO4_LOW_IRQ                      102
#define IMX_GPIO4_HIGH_IRQ                     103
#define IMX_GPIO5_LOW_IRQ                      104
#define IMX_GPIO5_HIGH_IRQ                     105

#define IMX_GPIO_CASCADE_IRQ(gpio_idx, pin_idx) (((gpio_idx - 1) * 32) + 544 + pin_idx)

/*
 * General Purpose Timer (GPT)
 */
#define IMX_GPT1_BASE                          0x302D0000
#define IMX_GPT2_BASE                          0x302E0000
#define IMX_GPT3_BASE                          0x302F0000
#define IMX_GPT4_BASE                          0x30700000
#define IMX_GPT5_BASE                          0x306F0000
#define IMX_GPT6_BASE                          0x306E0000

#define IMX_GPT_SIZE                           0x10000

#define IMX_GPT1_IRQ                           87
#define IMX_GPT2_IRQ                           86
#define IMX_GPT3_IRQ                           85
#define IMX_GPT4_IRQ                           84
#define IMX_GPT5_IRQ                           83

/*
 * IOMUX Controller (IOMUXC)
 */
#define IMX_IOMUXC_BASE                        0x30330000
#define IMX_IOMUXC_GPR_BASE                    0x30340000
#define IMX_IOMUXC_SIZE                        0x10000

/*
 * System Reset Controller (SRC)
 */
#define IMX_SRC_BASE                           0x30390000
#define IMX_SRC_SIZE                           0x10000

/*
 * General Power Controller (GPC)
 */
#define IMX_GPC_BASE                           0x303A0000
#define IMX_GPC_SIZE                           0x10000

/*
 * Universal Asynchronous Receiver/Transmitter (UART)
 */
#define IMX_UART1_BASE                         0x30860000
#define IMX_UART2_BASE                         0x30890000
#define IMX_UART3_BASE                         0x30880000
#define IMX_UART4_BASE                         0x30A60000

#define IMX_UART1_IRQ                          58
#define IMX_UART2_IRQ                          59
#define IMX_UART3_IRQ                          60
#define IMX_UART4_IRQ                          61

#define IMX_UART_SIZE                          0x10000
#define IMX_UART_COUNT                         4
/*
 * Enhanced Configurable Serial Peripheral Interface (eCSPI)
 */
#define IMX_ECSPI1_BASE                        0x30820000
#define IMX_ECSPI2_BASE                        0x30830000
#define IMX_ECSPI3_BASE                        0x30840000

#define IMX_ECSPI1_IRQ                         63
#define IMX_ECSPI2_IRQ                         64
#define IMX_ECSPI3_IRQ                         65

#define IMX_ECSPI_SIZE                         0x10000
#define IMX_ECSPI_COUNT                        3

/*
 * Ultra Secured Digital Host Controller (uSDHC)
 */
#define IMX_USDHC1_BASE                        0x30B40000
#define IMX_USDHC2_BASE                        0x30B50000
#define IMX_USDHC3_BASE                        0x30B60000

#define IMX_USDHC_SIZE                         0x10000
#define IMX_USDHC_COUNT                        3

#define IMX_USDHC1_IRQ                         54
#define IMX_USDHC2_IRQ                         55
#define IMX_USDHC3_IRQ                         56

/*
 * Quad Serial Peripheral Interface (QuadSPI)
 */
#define IMX_FLEXSPI0_BASE                      0x30BB0000

#define IMX_FLEXSPI_SIZE                       0x10000

#define IMX_FLEXSPI0_IRQ                       139

/*
 * System counter (SCTR)
 */
#define IMX_SCNTR_BASE                         0x306C0000
#define IMX_SCNTR_SIZE                         0x10000

/*
 * TrustZone Address Space Controller 380 (TZASC-380)
 */
#define IMX_TZASC_BASE                         0x32F80000
#define IMX_TZASC_SIZE                         0x10000

#define IMX_DDR_PHY_BASE                       0x3C000000
#define IMX_DDR_CTL_BASE                       0x3D400000

/*
 * USB OTG
 */
#define IMX_USB_OTG1_UOG1_BASE                  0x32E40000
#define IMX_USB_OTG1_UOG1_SIZE                  0x10000
#define IMX_USB_OTG1_UOG1_IRQ                   72

#define IMX_USB_OTG1_UOG2_BASE                  0x32E50000
#define IMX_USB_OTG1_UOG2_SIZE                  0x10000
#define IMX_USB_OTG1_UOG2_IRQ                   73

/*
 * On-Chip OTP Controller (OCOTP_CTRL)
 */
#define IMX_OCOTP_CTRL_BASE                     0x30350000
#define IMX_OCOTP_SIZE                          0x10000

/*
 * Watchdogs
 */
#define IMX_WDOG1_BASE                          0x30280000
#define IMX_WDOG2_BASE                          0x30290000
#define IMX_WDOG3_BASE                          0x302A0000

#define IMX_WDOG_SIZE                           0x1000

/*
 * Synchronous Audio Interface (SAI)
 */
#define IMX_SAI2_BASE                          0x30020000
#define IMX_SAI3_BASE                          0x30030000
#define IMX_SAI5_BASE                          0x30050000
#define IMX_SAI6_BASE                          0x30060000
#define IMX_SAI7_BASE                          0x300B0000

#define IMX_SAI2_IRQ                           (96 + 32)
#define IMX_SAI3_IRQ                           (50 + 32)
#define IMX_SAI5_IRQ                           (90 + 32)
#define IMX_SAI6_IRQ                           (90 + 32)
#define IMX_SAI7_IRQ                           (111 + 32)

#define IMX_SAI2_RX_EVENT                      2
#define IMX_SAI2_TX_EVENT                      3
#define IMX_SAI3_RX_EVENT                      4
#define IMX_SAI3_TX_EVENT                      5
#define IMX_SAI5_RX_EVENT                      8
#define IMX_SAI5_TX_EVENT                      9
#define IMX_SAI6_RX_EVENT                      10
#define IMX_SAI6_TX_EVENT                      11
#define IMX_SAI7_RX_EVENT                      12
#define IMX_SAI7_TX_EVENT                      13

#define IMX_SAI_SIZE                           0x10000

#endif /* IMXMN_SOC_H_ */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/hardware/branches/release/hardware/startup/boards/public/aarch64/mx8mn.h $ $Rev: 994161 $")
#endif
