/**
 * @file interrupt.h
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief holds interrupt numbers
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef INTERRUPT_H
#define INTERRUPT_H

#define IRQ_LINES 2 * 32 + 25 // ??



#define IRQ_TIMER_0             0
#define IRQ_TIMER_1             1
#define IRQ_TIMER_2             2
#define IRQ_TIMER_3             3

#define IRQ_H264_0              4
#define IRQ_H264_1              5
#define IRQ_H264_2              6

#define IRQ_JPEG                7
#define IRQ_ISP                 8
#define IRQ_USB                 9
#define IRQ_V3D                 10
#define IRQ_TRANSPOSER          11

#define IRQ_MULTICORE_SYNC_0    12
#define IRQ_MULTICORE_SYNC_1    13
#define IRQ_MULTICORE_SYNC_2    14
#define IRQ_MULTICORE_SYNC_3    15

#define IRQ_DMA_0               16
#define IRQ_DMA_1               17
#define IRQ_DMA_2               18
#define IRQ_DMA_3               19
#define IRQ_DMA_4               20
#define IRQ_DMA_5               21
#define IRQ_DMA_6               22
#define IRQ_DMA_7_and_8         23
#define IRQ_DMA_9_and_10        24
#define IRQ_DMA_11              25
#define IRQ_DMA_12              26
#define IRQ_DMA_13              27
#define IRQ_DMA_14              28


#define IRQ_AUX                 29
#define IRQ_ARM                 30
#define IRQ_VPUDMA              31 /// whats this?
#define IRQ_HDMI_CEC            32
#define IRQ_HVS                 33
#define IRQ_RPIVID              34
#define IRQ_SDC                 35
#define IRQ_DSI_0               36
#define IRQ_PIXEL_VALVE_2       37
#define IRQ_CAMERA_0            38
#define IRQ_CAMERA_1            39
#define IRQ_HDMI_0              40
#define IRQ_HDMI_1              41
#define IRQ_PIXEL_VALVE_3       42
#define IRQ_SPI_BSC_SLAVE       43
#define IRQ_DSI_1               44
#define IRQ_PIXEL_VALVE_0       45
#define IRQ_PIXEL_VALVE_1_and_4 46
#define IRQ_CPR                 47
#define IRQ_SMI                 48
#define IRQ_GPIO_0              49
#define IRQ_GPIO_1              50
#define IRQ_GPIO_2              51
#define IRQ_GPIO_3              52
#define IRQ_OR_of_all_I2C       53
#define IRQ_OR_of_all_SPI       54
#define IRQ_PCM_I2S             55
#define IRQ_SDHOST              56
#define IRQ_OR_of_all_PL011UART 57
#define IRQ_OR_of_all_ETH_PCIeL2 58
#define IRQ_VEC                 59
#define IRQ_CPG                 60
#define IRQ_RNG                 61
#define IRQ_EMMC_and_EMMC2      62
#define IRQ_ETH_PCIe_secure     63

#define GICD_BASE 0xff841000
#define GICD_CTRLR 		(GICD_BASE + 0x0)
#define GICD_TYPER      (GICD_BASE + 0x4)
#define GICD_IIDR 		(GICD_BASE + 0x8)
#define GICD_IGROUPR 	(GICD_BASE + 0x80)
#define GICD_ISENABLER 	(GICD_BASE + 0x100)
#define GICD_ICENABLER  (GICD_BASE + 0x180)
#define GICD_ISPENDR 	(GICD_BASE + 0x200)
#define GICD_ICPENDR 	(GICD_BASE + 0x280)
#define GICD_ISACTIVER 	(GICD_BASE + 0x300)
#define GICD_ICACTIVER 	(GICD_BASE + 0x380)
#define GICD_IPRIORITYR (GICD_BASE + 0x400)
#define GICD_ITARGETSR 	(GICD_BASE + 0x800)
#define GICD_ICFGR 		(GICD_BASE + 0xC00)
#define GICD_PPISR 		(GICD_BASE + 0xD00)
#define GICD_SPISR 		(GICD_BASE + 0xD04)
#define GICD_SGIR 		(GICD_BASE + 0xF00)
#define GICD_CPENDSGIR 	(GICD_BASE + 0xF10)
#define GICD_SPENDSGIR 	(GICD_BASE + 0xF20)

#define GICC_BASE 0xff842000
#define GICC_CTRLR 		(GICC_BASE + 0x0)
#define GICC_PMR 		(GICC_BASE + 0x4)
#define GICC_BPR 		(GICC_BASE + 0x8)
#define GICC_IAR 		(GICC_BASE + 0xC)
#define GICC_EOIR 		(GICC_BASE + 0x10)
#define GICC_RPR 		(GICC_BASE + 0x14)
#define GICC_HPPIR 		(GICC_BASE + 0x18)
#define GICC_ABPR 		(GICC_BASE + 0x1C)
#define GICC_AIAR 		(GICC_BASE + 0x20)
#define GICC_AEOIR 		(GICC_BASE + 0x24)
#define GICC_AHPPIR 	(GICC_BASE + 0x28)
#define GICC_APR0 		(GICC_BASE + 0xD0)
#define GICC_NSAPR0 	(GICC_BASE + 0xE0)
#define GICC_IIDR 		(GICC_BASE + 0xFC)
#define GIC_DIR 		(GICC_BASE + 0x1000)

#endif // INTERRUPT_H