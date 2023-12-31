/**
 * @file bcm2711.h
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief register address constants for BCM2711
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef BCM2711_H
#define BCM2711_H

#define ARM_IO_BASE		0xFE000000
#define ARM_IO_END		(ARM_IO_BASE + 0xFFFFFF)


#define GPU_IO_BASE		0x7E000000

#define GPU_CACHED_BASE		0x40000000
#define GPU_UNCACHED_BASE	0xC0000000


//
// General Purpose I/O
//
#define ARM_GPIO_BASE    (ARM_IO_BASE + 0x200000)

#define ARM_GPIO_GPFSEL0 (ARM_GPIO_BASE + 0x00)
#define ARM_GPIO_GPFSEL1 (ARM_GPIO_BASE + 0x04)
#define ARM_GPIO_GPFSEL2 (ARM_GPIO_BASE + 0x08)
#define ARM_GPIO_GPFSEL3 (ARM_GPIO_BASE + 0x0c)
#define ARM_GPIO_GPFSEL4 (ARM_GPIO_BASE + 0x10)
#define ARM_GPIO_GPFSEL5 (ARM_GPIO_BASE + 0x14)
#define ARM_GPIO_GPSET0 (ARM_GPIO_BASE + 0x1c)
#define ARM_GPIO_GPSET1 (ARM_GPIO_BASE + 0x20)
#define ARM_GPIO_GPCLR0 (ARM_GPIO_BASE + 0x28)
#define ARM_GPIO_GPCLR1 (ARM_GPIO_BASE + 0x2c)
#define ARM_GPIO_GPLEV0 (ARM_GPIO_BASE + 0x34)
#define ARM_GPIO_GPLEV1 (ARM_GPIO_BASE + 0x38)
#define ARM_GPIO_GPEDS0 (ARM_GPIO_BASE + 0x40)
#define ARM_GPIO_GPEDS1 (ARM_GPIO_BASE + 0x44)
#define ARM_GPIO_GPREN0 (ARM_GPIO_BASE + 0x4c)
#define ARM_GPIO_GPREN1 (ARM_GPIO_BASE + 0x50)
#define ARM_GPIO_GPFEN0 (ARM_GPIO_BASE + 0x58)
#define ARM_GPIO_GPFEN1 (ARM_GPIO_BASE + 0x5c)
#define ARM_GPIO_GPFHEN0 (ARM_GPIO_BASE + 0x64)
#define ARM_GPIO_GPHEN1 (ARM_GPIO_BASE + 0x68)
#define ARM_GPIO_GPLEN0 (ARM_GPIO_BASE + 0x70)
#define ARM_GPIO_GPLEN1 (ARM_GPIO_BASE + 0x74)
#define ARM_GPIO_GPAREN0 (ARM_GPIO_BASE + 0x7c)
#define ARM_GPIO_GPAREN1 (ARM_GPIO_BASE + 0x80)
#define ARM_GPIO_GPAFEN0 (ARM_GPIO_BASE + 0x88)
#define ARM_GPIO_GPAFEN1 (ARM_GPIO_BASE + 0x8c)
#define ARM_GPIO_GPIO_PUPDNN0 (ARM_GPIO_BASE + 0xe4)
#define ARM_GPIO_GPIO_PUPDNN1 (ARM_GPIO_BASE + 0xe8)
#define ARM_GPIO_GPIO_PUPDNN2 (ARM_GPIO_BASE + 0xec)
#define ARM_GPIO_GPIO_PUPDNN3 (ARM_GPIO_BASE + 0xf0)


//
// Auxiliary Peripherals
//


#define ARM_AUX_BASE (ARM_IO_BASE + 0x215000)
#define ARM_AUX_IRQ (ARM_AUX_BASE + 0x00)
#define ARM_AUX_ENABLES (ARM_AUX_BASE + 0x04)
#define ARM_AUX_MU_IO_REG (ARM_AUX_BASE + 0x40)
#define ARM_AUX_MU_IER_REG (ARM_AUX_BASE + 0x44)
#define ARM_AUX_MU_IIR_REG (ARM_AUX_BASE + 0x48)
#define ARM_AUX_MU_LCR_REG (ARM_AUX_BASE + 0x4c)
#define ARM_AUX_MU_MCR_REG (ARM_AUX_BASE + 0x50)
#define ARM_AUX_MU_LSR_REG (ARM_AUX_BASE + 0x54)
#define ARM_AUX_MU_MSR_REG (ARM_AUX_BASE + 0x58)
#define ARM_AUX_MU_SCRATCH (ARM_AUX_BASE + 0x5c)
#define ARM_AUX_MU_CNTL_REG (ARM_AUX_BASE + 0x60)
#define ARM_AUX_MU_STAT_REG (ARM_AUX_BASE + 0x64)
#define ARM_AUX_MU_BAUD_REG (ARM_AUX_BASE + 0x68)
#define ARM_AUX_SPI1_CNTL0_REGSP (ARM_AUX_BASE + 0x80)
#define ARM_AUX_SPI1_CNTL1_REGSP (ARM_AUX_BASE + 0x84)
#define ARM_AUX_SPI1_STAT_REGSP (ARM_AUX_BASE + 0x88)
#define ARM_AUX_SPI1_PEEK_REGSP (ARM_AUX_BASE + 0x8c)
#define ARM_AUX_SPI1_IO_REa (ARM_AUX_BASE + 0xa0)
#define ARM_AUX_SPI1_IO_REb (ARM_AUX_BASE + 0xa4)
#define ARM_AUX_SPI1_IO_REc (ARM_AUX_BASE + 0xa8)
#define ARM_AUX_SPI1_IO_REd (ARM_AUX_BASE + 0xac)
#define ARM_AUX_SPI1_TXHOLD_REa (ARM_AUX_BASE + 0xb0)
#define ARM_AUX_SPI1_TXHOLD_REb (ARM_AUX_BASE + 0xb4)
#define ARM_AUX_SPI1_TXHOLD_REc (ARM_AUX_BASE + 0xb8)
#define ARM_AUX_SPI1_TXHOLD_REd (ARM_AUX_BASE + 0xbc)
#define ARM_AUX_SPI2_CNTL0_REGSP (ARM_AUX_BASE + 0xc0)
#define ARM_AUX_SPI2_CNTL1_REGSP (ARM_AUX_BASE + 0xc4)
#define ARM_AUX_SPI2_STAT_REGSP (ARM_AUX_BASE + 0xc8)
#define ARM_AUX_SPI2_PEEK_REGSP (ARM_AUX_BASE + 0xcc)
#define ARM_AUX_SPI2_IO_REa (ARM_AUX_BASE + 0xe0)
#define ARM_AUX_SPI2_IO_REb (ARM_AUX_BASE + 0xe4)
#define ARM_AUX_SPI2_IO_REc (ARM_AUX_BASE + 0xe8)
#define ARM_AUX_SPI2_IO_REd (ARM_AUX_BASE + 0xec)
#define ARM_AUX_SPI2_TXHOLD_REa (ARM_AUX_BASE + 0xf0)
#define ARM_AUX_SPI2_TXHOLD_REb (ARM_AUX_BASE + 0xf4)
#define ARM_AUX_SPI2_TXHOLD_REc (ARM_AUX_BASE + 0xf8)
#define ARM_AUX_SPI2_TXHOLD_REd (ARM_AUX_BASE + 0xfc)


//
// System Timers
//
#define ARM_SYSTIMER_BASE	(ARM_IO_BASE + 0x3000)

#define ARM_SYSTIMER_CS		(ARM_SYSTIMER_BASE + 0x00)
#define ARM_SYSTIMER_CLO	(ARM_SYSTIMER_BASE + 0x04)
#define ARM_SYSTIMER_CHI	(ARM_SYSTIMER_BASE + 0x08)
#define ARM_SYSTIMER_C0		(ARM_SYSTIMER_BASE + 0x0C)
#define ARM_SYSTIMER_C1		(ARM_SYSTIMER_BASE + 0x10)
#define ARM_SYSTIMER_C2		(ARM_SYSTIMER_BASE + 0x14)
#define ARM_SYSTIMER_C3		(ARM_SYSTIMER_BASE + 0x18)

//
// Platform DMA Controller
//
#define ARM_DMA_BASE		(ARM_IO_BASE + 0x7000)

//
// Interrupt Controller
//

/// ARM_LOCAL
/// BCM2711-peripherals.pdf, page 92

#define ARM_LOCAL_BASE		(ARM_IO_BASE + 0x1000000)

#define ARM_LOCAL_ARM_CONTROL			(ARM_LOCAL_BASE + 0x000)
#define ARM_LOCAL_CORE_IRQ_CONTROL	(ARM_LOCAL_BASE + 0x00c)
#define ARM_LOCAL_PMU_CONTROL_SET		(ARM_LOCAL_BASE + 0x010)
#define ARM_LOCAL_PMU_CONTROL_CLR		(ARM_LOCAL_BASE + 0x014)
#define ARM_LOCAL_PERI_IRQ_ROUTE0 	(ARM_LOCAL_BASE + 0x024)
#define ARM_LOCAL_AXI_QUIET_TIME		(ARM_LOCAL_BASE + 0x030)
#define ARM_LOCAL_TIMER_CONTROL	(ARM_LOCAL_BASE + 0x034)
#define ARM_LOCAL_TIMER_IRQ    	(ARM_LOCAL_BASE + 0x038)
#define ARM_LOCAL_TIMER_CNTRL0		(ARM_LOCAL_BASE + 0x040)
#define ARM_LOCAL_TIMER_CNTRL1		(ARM_LOCAL_BASE + 0x044)
#define ARM_LOCAL_TIMER_CNTRL2		(ARM_LOCAL_BASE + 0x048)
#define ARM_LOCAL_TIMER_CNTRL3		(ARM_LOCAL_BASE + 0x04C)
#define ARM_LOCAL_MAILBOX_CNTRL0		(ARM_LOCAL_BASE + 0x050)
#define ARM_LOCAL_MAILBOX_CNTRL1		(ARM_LOCAL_BASE + 0x054)
#define ARM_LOCAL_MAILBOX_CNTRL2		(ARM_LOCAL_BASE + 0x058)
#define ARM_LOCAL_MAILBOX_CNTRL3		(ARM_LOCAL_BASE + 0x05C)
#define ARM_LOCAL_IRQ_SOURCE0			(ARM_LOCAL_BASE + 0x060)
#define ARM_LOCAL_IRQ_SOURCE1			(ARM_LOCAL_BASE + 0x064)
#define ARM_LOCAL_IRQ_SOURCE2			(ARM_LOCAL_BASE + 0x068)
#define ARM_LOCAL_IRQ_SOURCE3			(ARM_LOCAL_BASE + 0x06C)
#define ARM_LOCAL_FIQ_SOURCE0			(ARM_LOCAL_BASE + 0x070)
#define ARM_LOCAL_FIQ_SOURCE1			(ARM_LOCAL_BASE + 0x074)
#define ARM_LOCAL_FIQ_SOURCE2			(ARM_LOCAL_BASE + 0x078)
#define ARM_LOCAL_FIQ_SOURCE3			(ARM_LOCAL_BASE + 0x07C)


/// ARMC
/// BCM2711-peripherals.pdf, page 100

#define ARMC_BASE			(ARM_IO_BASE + 0xB000)
/// first the IRQs
#define ARMC_IRQ0_PENDING0 		(ARMC_BASE + 0x200) /// interrupts 0..31 from interrupt.h
#define ARMC_IRQ0_PENDING1 		(ARMC_BASE + 0x204) /// interrupts 32..63 from interrupt.h
/*
 *	bit 25 is the OR of interrupts 63..32, if set then read PENDING_1
 *	bit 24 is the OR of interrupts 31..0, if set then read PENDING_0
 */
#define ARMC_IRQ0_PENDING2 		(ARMC_BASE + 0x208)
#define ARMC_IRQ0_SET_EN_0 		(ARMC_BASE + 0x210)
#define ARMC_IRQ0_SET_EN_1 		(ARMC_BASE + 0x214)
#define ARMC_IRQ0_SET_EN_2 		(ARMC_BASE + 0x218)
#define ARMC_IRQ0_CLR_EN_0 		(ARMC_BASE + 0x220)
#define ARMC_IRQ0_CLR_EN_1 		(ARMC_BASE + 0x224)
#define ARMC_IRQ0_CLR_EN_2 		(ARMC_BASE + 0x228)

#define ARMC_IRQ_STATUS0 		(ARMC_BASE + 0x230)
#define ARMC_IRQ_STATUS1 		(ARMC_BASE + 0x234)
#define ARMC_IRQ_STATUS2 		(ARMC_BASE + 0x238)

#define ARMC_IRQ1_PENDING0 		(ARMC_BASE + 0x240)
#define ARMC_IRQ1_PENDING1 		(ARMC_BASE + 0x244)
#define ARMC_IRQ1_PENDING2 		(ARMC_BASE + 0x248)
#define ARMC_IRQ1_SET_EN_0 		(ARMC_BASE + 0x250)
#define ARMC_IRQ1_SET_EN_1 		(ARMC_BASE + 0x254)
#define ARMC_IRQ1_SET_EN_2 		(ARMC_BASE + 0x258)
#define ARMC_IRQ1_CLR_EN_0 		(ARMC_BASE + 0x260)
#define ARMC_IRQ1_CLR_EN_1 		(ARMC_BASE + 0x264)
#define ARMC_IRQ1_CLR_EN_2 		(ARMC_BASE + 0x268)

#define ARMC_IRQ2_PENDING0 		(ARMC_BASE + 0x280)
#define ARMC_IRQ2_PENDING1 		(ARMC_BASE + 0x284)
#define ARMC_IRQ2_PENDING2 		(ARMC_BASE + 0x288)
#define ARMC_IRQ2_SET_EN_0 		(ARMC_BASE + 0x290)
#define ARMC_IRQ2_SET_EN_1 		(ARMC_BASE + 0x294)
#define ARMC_IRQ2_SET_EN_2 		(ARMC_BASE + 0x298)
#define ARMC_IRQ2_CLR_EN_0 		(ARMC_BASE + 0x2A0)
#define ARMC_IRQ2_CLR_EN_1 		(ARMC_BASE + 0x2A4)
#define ARMC_IRQ2_CLR_EN_2 		(ARMC_BASE + 0x2A8)

#define ARMC_IRQ3_PENDING0 		(ARMC_BASE + 0x2C0)
#define ARMC_IRQ3_PENDING1 		(ARMC_BASE + 0x2C4)
#define ARMC_IRQ3_PENDING2 		(ARMC_BASE + 0x2C8)
#define ARMC_IRQ3_SET_EN_0 		(ARMC_BASE + 0x2D0)
#define ARMC_IRQ3_SET_EN_1 		(ARMC_BASE + 0x2D4)
#define ARMC_IRQ3_SET_EN_2 		(ARMC_BASE + 0x2D8)
#define ARMC_IRQ3_CLR_EN_0 		(ARMC_BASE + 0x2E0)
#define ARMC_IRQ3_CLR_EN_1 		(ARMC_BASE + 0x2E4)
#define ARMC_IRQ3_CLR_EN_2 		(ARMC_BASE + 0x2E8)

/// then the FIQs, not used so far, so not many defines
#define ARMC_FIQ0_PENDING0 		(ARMC_BASE + 0x300)
#define ARMC_FIQ0_PENDING1 		(ARMC_BASE + 0x304)
#define ARMC_FIQ0_PENDING2 		(ARMC_BASE + 0x308)
#define ARMC_FIQ0_SET_EN_0 		(ARMC_BASE + 0x310)
#define ARMC_FIQ0_SET_EN_1 		(ARMC_BASE + 0x314)
#define ARMC_FIQ0_SET_EN_2 		(ARMC_BASE + 0x318)
#define ARMC_FIQ0_CLR_EN_0 		(ARMC_BASE + 0x320)
#define ARMC_FIQ0_CLR_EN_1 		(ARMC_BASE + 0x324)
#define ARMC_FIQ0_CLR_EN_2 		(ARMC_BASE + 0x328)
///... and so on

#define ARMC_SWIRQ_SET 			(ARMC_BASE + 0x3f0)
#define ARMC_SWIRQ_CLR 			(ARMC_BASE + 0x3f4)

//
// ARM Timer
//
#define ARM_TIMER_BASE		(ARM_IO_BASE + 0xB000)

#define ARM_TIMER_LOAD		(ARM_TIMER_BASE + 0x400)
#define ARM_TIMER_VALUE		(ARM_TIMER_BASE + 0x404)
#define ARM_TIMER_CONTROL	(ARM_TIMER_BASE + 0x408)
#define ARM_TIMER_IRQCLR	(ARM_TIMER_BASE + 0x40C)
#define ARM_TIMER_RAWIRQ	(ARM_TIMER_BASE + 0x410)
#define ARM_TIMER_MASKIRQ	(ARM_TIMER_BASE + 0x414)
#define ARM_TIMER_RELOAD	(ARM_TIMER_BASE + 0x418)
#define ARM_TIMER_PREDIV	(ARM_TIMER_BASE + 0x41C)
#define ARM_TIMER_FREECNT	(ARM_TIMER_BASE + 0x420)

//
// Mailbox
//
#define MAILBOX_BASE		(ARM_IO_BASE + 0xB880)

#define MAILBOX_OFFSET  0x20
#define MAILBOX_READ_OFFSET 0x00
#define MAILBOX_POLL_OFFSET 0x10
#define MAILBOX_

#define MAILBOX0_READ  		(MAILBOX_BASE + 0x00)
#define MAILBOX0_POLL		(MAILBOX_BASE + 0x10)
#define MAILBOX0_SENDER		(MAILBOX_BASE + 0x14)
#define MAILBOX0_STATUS 	(MAILBOX_BASE + 0x18)
#define MAILBOX0_CONFIG 	(MAILBOX_BASE + 0x1C)
#define MAILBOX0_WRITE		(MAILBOX_BASE + 0x20)
#define MAILBOX1_READ  		(MAILBOX_BASE + 0x00)
#define MAILBOX1_POLL		(MAILBOX_BASE + 0x10)
#define MAILBOX1_SENDER		(MAILBOX_BASE + 0x14)
#define MAILBOX1_STATUS 	(MAILBOX_BASE + 0x18)
#define MAILBOX1_CONFIG 	(MAILBOX_BASE + 0x1C)
#define MAILBOX1_WRITE		(MAILBOX_BASE + 0x20)

#define MAILBOX_CH_PM	0			// power management
#define MAILBOX_CH_FB 	1			// frame buffer
#define BCM_MAILBOX_PROP_OUT	8			// property tags (ARM to VC)

//
// Pulse Width Modulator
//
#define ARM_PWM_BASE		(ARM_IO_BASE + 0x20C000)

#define ARM_PWM_CTL		(ARM_PWM_BASE + 0x00)
#define ARM_PWM_STA		(ARM_PWM_BASE + 0x04)
#define ARM_PWM_DMAC		(ARM_PWM_BASE + 0x08)
#define ARM_PWM_RNG1		(ARM_PWM_BASE + 0x10)
#define ARM_PWM_DAT1		(ARM_PWM_BASE + 0x14)
#define ARM_PWM_FIF1		(ARM_PWM_BASE + 0x18)
#define ARM_PWM_RNG2		(ARM_PWM_BASE + 0x20)
#define ARM_PWM_DAT2		(ARM_PWM_BASE + 0x24)
#define ARM_PWM1_BASE		(ARM_IO_BASE + 0x20C800)

#define ARM_PWM1_CTL		(ARM_PWM1_BASE + 0x00)
#define ARM_PWM1_STA		(ARM_PWM1_BASE + 0x04)
#define ARM_PWM1_DMAC		(ARM_PWM1_BASE + 0x08)
#define ARM_PWM1_RNG1		(ARM_PWM1_BASE + 0x10)
#define ARM_PWM1_DAT1		(ARM_PWM1_BASE + 0x14)
#define ARM_PWM1_FIF1		(ARM_PWM1_BASE + 0x18)
#define ARM_PWM1_RNG2		(ARM_PWM1_BASE + 0x20)
#define ARM_PWM1_DAT2		(ARM_PWM1_BASE + 0x24)

//
// Clock Manager
//
#define ARM_CM_BASE		(ARM_IO_BASE + 0x101000)

#define ARM_CM_CAM0CTL		(ARM_CM_BASE + 0x40)
#define ARM_CM_CAM0DIV		(ARM_CM_BASE + 0x44)
#define ARM_CM_CAM1CTL		(ARM_CM_BASE + 0x48)
#define ARM_CM_CAM1DIV		(ARM_CM_BASE + 0x4C)

#define ARM_CM_GP0CTL		(ARM_CM_BASE + 0x70)
#define ARM_CM_GP0DIV		(ARM_CM_BASE + 0x74)

#define ARM_CM_SMICTL		(ARM_CM_BASE + 0xB0)
#define ARM_CM_SMIDIV		(ARM_CM_BASE + 0xB4)

#define ARM_CM_PASSWD 		(0x5A << 24)

//
// USB Host Controller
//
#define ARM_USB_BASE		(ARM_IO_BASE + 0x980000)

#define ARM_USB_CORE_BASE	ARM_USB_BASE
#define ARM_USB_HOST_BASE	(ARM_USB_BASE + 0x400)
#define ARM_USB_DEV_BASE	(ARM_USB_BASE + 0x800)
#define ARM_USB_POWER		(ARM_USB_BASE + 0xE00)

//
// Host Port (MPHI)
//
#define ARM_MPHI_BASE		(ARM_IO_BASE + 0x6000)
#define ARM_MPHI_END		(ARM_IO_BASE + 0x6FFF)

#define ARM_MPHI_OUTDDA		(ARM_MPHI_BASE + 0x28)
#define ARM_MPHI_OUTDDB		(ARM_MPHI_BASE + 0x2C)
#define ARM_MPHI_CTRL		(ARM_MPHI_BASE + 0x4C)
#define ARM_MPHI_INTSTAT	(ARM_MPHI_BASE + 0x50)

//
// External Mass Media Controller (SD Card)
//
#define ARM_EMMC_BASE		(ARM_IO_BASE + 0x300000)

//
// SDHOST Controller (SD Card)
//
#define ARM_SDHOST_BASE		(ARM_IO_BASE + 0x202000)

//
// Power Manager
//
#define ARM_PM_BASE		(ARM_IO_BASE + 0x100000)

#define ARM_PM_RSTC		(ARM_PM_BASE + 0x1C)
#define ARM_PM_RSTS		(ARM_PM_BASE + 0x20)
#define ARM_PM_WDOG		(ARM_PM_BASE + 0x24)
#define ARM_PM_PADS0		(ARM_PM_BASE + 0x2C)    // GPIO 0 - 27
#define ARM_PM_PADS1		(ARM_PM_BASE + 0x30)    // GPIO 28 - 45
#define ARM_PM_PADS2		(ARM_PM_BASE + 0x34)    // GPIO 46 - 53

#define ARM_PM_PASSWD		(0x5A << 24)
#define ARM_PM_RSTC_CLEAR	0xFFFFFFCF
#define ARM_PM_RSTC_REBOOT	0x00000020
#define ARM_PM_RSTC_RESET	0x00000102
#define ARM_PM_RSTS_PART_CLEAR	0xFFFFFAAA
#define ARM_PM_WDOG_TIME	0x000FFFFF
#define ARM_PADS_SLEW		(0x01 << 4)
#define ARM_PADS_HYST		(0x01 << 3)
#define ARM_PADS_DRIVE(val)	((val) & 0x3)

//
// BSC Master
//
#define ARM_BSC0_BASE		(ARM_IO_BASE + 0x205000)
#define ARM_BSC1_BASE		(ARM_IO_BASE + 0x804000)

#define ARM_BSC_C__OFFSET	0x00
#define ARM_BSC_S__OFFSET	0x04
#define ARM_BSC_DLEN__OFFSET	0x08
#define ARM_BSC_A__OFFSET	0x0C
#define ARM_BSC_FIFO__OFFSET	0x10
#define ARM_BSC_DIV__OFFSET	0x14
#define ARM_BSC_DEL__OFFSET	0x18
#define ARM_BSC_CLKT__OFFSET	0x1C

//
// SPI0 Master
//
#define ARM_SPI0_BASE		(ARM_IO_BASE + 0x204000)

#define ARM_SPI0_CS		(ARM_SPI0_BASE + 0x00)
#define ARM_SPI0_FIFO		(ARM_SPI0_BASE + 0x04)
#define ARM_SPI0_CLK		(ARM_SPI0_BASE + 0x08)
#define ARM_SPI0_DLEN		(ARM_SPI0_BASE + 0x0C)
#define ARM_SPI0_LTOH		(ARM_SPI0_BASE + 0x10)
#define ARM_SPI0_DC		(ARM_SPI0_BASE + 0x14)

//
// BSC / SPI Slave
//
#define ARM_BSC_SPI_SLAVE_BASE	(ARM_IO_BASE + 0x214000)

#define ARM_BSC_SPI_SLAVE_DR	(ARM_BSC_SPI_SLAVE_BASE + 0x00)
#define ARM_BSC_SPI_SLAVE_RSR	(ARM_BSC_SPI_SLAVE_BASE + 0x04)
#define ARM_BSC_SPI_SLAVE_SLV	(ARM_BSC_SPI_SLAVE_BASE + 0x08)
#define ARM_BSC_SPI_SLAVE_CR	(ARM_BSC_SPI_SLAVE_BASE + 0x0C)
#define ARM_BSC_SPI_SLAVE_FR	(ARM_BSC_SPI_SLAVE_BASE + 0x10)
#define ARM_BSC_SPI_SLAVE_IFLS	(ARM_BSC_SPI_SLAVE_BASE + 0x14)
#define ARM_BSC_SPI_SLAVE_IMSC	(ARM_BSC_SPI_SLAVE_BASE + 0x18)
#define ARM_BSC_SPI_SLAVE_RIS	(ARM_BSC_SPI_SLAVE_BASE + 0x1C)
#define ARM_BSC_SPI_SLAVE_MIS	(ARM_BSC_SPI_SLAVE_BASE + 0x20)
#define ARM_BSC_SPI_SLAVE_ICR	(ARM_BSC_SPI_SLAVE_BASE + 0x24)

//
// Hardware Random Number Generator
//
#define ARM_HW_RNG_BASE		(ARM_IO_BASE + 0x104000)

#define ARM_HW_RNG_CTRL		(ARM_HW_RNG_BASE + 0x00)
	#define ARM_HW_RNG_CTRL_EN	0x01
#define ARM_HW_RNG_STATUS	(ARM_HW_RNG_BASE + 0x04)
#define ARM_HW_RNG_DATA		(ARM_HW_RNG_BASE + 0x08)

//
// PCM / I2S Audio Module
//
#define ARM_PCM_BASE		(ARM_IO_BASE + 0x203000)

#define ARM_PCM_CS_A		(ARM_PCM_BASE + 0x00)
#define ARM_PCM_FIFO_A		(ARM_PCM_BASE + 0x04)
#define ARM_PCM_MODE_A		(ARM_PCM_BASE + 0x08)
#define ARM_PCM_RXC_A		(ARM_PCM_BASE + 0x0C)
#define ARM_PCM_TXC_A		(ARM_PCM_BASE + 0x10)
#define ARM_PCM_DREQ_A		(ARM_PCM_BASE + 0x14)
#define ARM_PCM_INTEN_A		(ARM_PCM_BASE + 0x18)
#define ARM_PCM_INTSTC_A	(ARM_PCM_BASE + 0x1C)
#define ARM_PCM_GRAY		(ARM_PCM_BASE + 0x20)

//
// VC4 VCHIQ
//
#define ARM_VCHIQ_BASE		(ARM_IO_BASE + 0xB840)
#define ARM_VCHIQ_END		(ARM_VCHIQ_BASE + 0x0F)

//
// VC4/5 HDMI
//
#if RASPPI <= 3
#define ARM_HDMI_BASE		(ARM_IO_BASE + 0x902000)
#define ARM_HD_BASE		(ARM_IO_BASE + 0x808000)
#else
#define ARM_HDMI_BASE		(ARM_IO_BASE + 0xF00700)
#define ARM_HD_BASE		(ARM_IO_BASE + 0xF20000)
#define ARM_PHY_BASE		(ARM_IO_BASE + 0xF00F00)
#define ARM_RAM_BASE		(ARM_IO_BASE + 0xF01B00)
#endif

//
// CSI
//
#define ARM_CSI0_BASE		(ARM_IO_BASE + 0x800000)
#define ARM_CSI0_END		(ARM_CSI0_BASE + 0x7FF)
#define ARM_CSI0_CLKGATE	(ARM_IO_BASE + 0x802000)	// 4 bytes

#define ARM_CSI1_BASE		(ARM_IO_BASE + 0x801000)
#define ARM_CSI1_END		(ARM_CSI1_BASE + 0x7FF)
#define ARM_CSI1_CLKGATE	(ARM_IO_BASE + 0x802004)	// 4 bytes


#endif // BCM2711_H
