#include <sysconfig.h>

/* Taken from U-Boot, defined in arch/arm/include/asm/macro.h */
.macro armv8_switch_to_el1_m, xreg1, xreg2

		/* Initialize Generic Timers */
		mrs	\xreg1, cnthctl_el2
		orr	\xreg1, \xreg1, #0x3	/* Enable EL1 access to timers */
		msr	cnthctl_el2, \xreg1
		msr	cntvoff_el2, xzr

		/* Initilize MPID/MPIDR registers */
		mrs	\xreg1, midr_el1
		mrs	\xreg2, mpidr_el1
		msr	vpidr_el2, \xreg1
		msr	vmpidr_el2, \xreg2

		/* Disable coprocessor traps */
		mov	\xreg1, #0x33ff
		msr	cptr_el2, \xreg1	/* Disable coprocessor traps to EL2 */
		msr	hstr_el2, xzr		/* Disable coprocessor traps to EL2 */
		mov	\xreg1, #3 << 20
		msr	cpacr_el1, \xreg1	/* Enable FP/SIMD at EL1 */

		/* Initialize HCR_EL2 */
		mov	\xreg1, #(1 << 31)		/* 64bit EL1 */
		msr	hcr_el2, \xreg1

		/* SCTLR_EL1 initialization
		*
		* setting RES1 bits (29,28,23,22,20,11) to 1
		* and RES0 bits (31,30,27,21,17,13,10,6) +
		* UCI,EE,EOE,WXN,nTWE,nTWI,UCT,DZE,I,UMA,SED,ITD,
		* CP15BEN,SA0,SA,C,A,M to 0
		*/
		mov	\xreg1, #0x0800
		movk	\xreg1, #0x30d0, lsl #16
		msr	sctlr_el1, \xreg1

		/* Return to the EL1_SP1 mode from EL2 */
		mov	\xreg1, #0x3c4
		msr	spsr_el2, \xreg1	/* EL1_SP0 | D | A | I | F */
		adr	\xreg1, 1f
		msr	elr_el2, \xreg1
		eret
1:

.endm

.section .boot  // Make sure the linker puts this at the start of the kernel image
.global _start
_start:
		mrs	x2, mpidr_el1		/* read affinity */
		and	x2, x2, #CORES-1	/* get CPU ID */

		mrs	x0, CurrentEL		/* check if already in EL1t mode? */
		cmp	x0, #4
		beq	1f

		mov	x1, #EXCEPTION_STACK_SIZE /* calculate exception stack offset for core */
		mul	x1, x1, x2
		ldr	x0, =MEM_EXCEPTION_STACK /* IRQ, FIQ and exception handler run in EL1h */
		add	x0, x0, x1
		msr	sp_el1, x0		/* init their stack */

		armv8_switch_to_el1_m x0, x1

1:		mov	x1, #KERNEL_STACK_SIZE	/* calculate kernel stack offset for core */
		mul	x1, x1, x2
		ldr	x0, =MEM_KERNEL_STACK	/* main thread runs in EL1t and uses sp_el0 */
		add	x0, x0, x1
		mov	sp, x0			/* init its stack */

		ldr	x0, =VectorTable	/* init exception vector table */
		msr	vbar_el1, x0

		b	_Z7sysinitv