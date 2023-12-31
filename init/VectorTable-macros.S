/**
 * @file VectorTable-macros.S
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief macros used in VectorTable.S
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

.macro kernel_entry
	sub sp, sp, #256
	stp x0, x1, [sp, #16 * 0]
	stp x2, x3, [sp, #16 * 1]
	stp x4, x5, [sp, #16 * 2]
	stp x6, x7, [sp, #16 * 3]
	stp x8, x9, [sp, #16 * 4]
	stp x10, x11, [sp, #16 * 5]
	stp x12, x13, [sp, #16 * 6]
	stp x14, x15, [sp, #16 * 7]
	stp x16, x17, [sp, #16 * 8]
	stp x18, x19, [sp, #16 * 9]
	stp x20, x21, [sp, #16 * 10]
	stp x22, x23, [sp, #16 * 11]
	stp x24, x25, [sp, #16 * 12]
	stp x26, x27, [sp, #16 * 13]
	stp x28, x29, [sp, #16 * 14]
	str x30, [sp, #16 * 15]
	.endm

.macro kernel_exit
	ldp x0, x1, [sp, #16 * 0]
	ldp x2, x3, [sp, #16 * 1]
	ldp x4, x5, [sp, #16 * 2]
	ldp x6, x7, [sp, #16 * 3]
	ldp x8, x9, [sp, #16 * 4]
	ldp x10, x11, [sp, #16 * 5]
	ldp x12, x13, [sp, #16 * 6]
	ldp x14, x15, [sp, #16 * 7]
	ldp x16, x17, [sp, #16 * 8]
	ldp x18, x19, [sp, #16 * 9]
	ldp x20, x21, [sp, #16 * 10]
	ldp x22, x23, [sp, #16 * 11]
	ldp x24, x25, [sp, #16 * 12]
	ldp x26, x27, [sp, #16 * 13]
	ldp x28, x29, [sp, #16 * 14]
	ldr x30, [sp, #16 * 15]
	add sp, sp, #256
	.endm
	
	



.macro	ventry label

	.align	7

	b	\label

	.endm
	
	
.macro	stub name, exception

	.globl	\name
\name:
	mrs	x0, esr_el1 		/* exception syndrome */
	mrs	x1, spsr_el1		/* saved program status */
	mov	x2, x30				/* link register */
	mrs	x3, elr_el1			/* return address */
	mrs	x4, sp_el0			/* sp_el0 */
	mov	x5, sp				/* sp_elx */
	mrs	x6, far_el1			/* fault address */

	str	x6, [sp, #-16]!
	stp	x4, x5, [sp, #-16]!
	stp	x2, x3, [sp, #-16]!
	stp	x0, x1, [sp, #-16]!

	mov	x0, #\exception
	mov	x1, sp
	b	HandleException		 /*never returns */

	.endm
