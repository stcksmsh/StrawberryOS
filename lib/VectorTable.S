#include <exception.h>
#include <bcm2711.h>
#include "VectorTable-macros.S"

	.text

	.align 11

.globl VectorTable
VectorTable:


	/* from EL1 with sp_el0, that is sp_sel == 0 */
	ventry	SynchronousStub
	ventry	IRQStub
	ventry	UnexpectedStub /// not using FIQs
	ventry	SErrorStub

	/* from EL1 with sp_el1, that is sp_sel == 1 */
	ventry	SynchronousStub
	ventry	IRQStub
	ventry	UnexpectedStub /// not using FIQs
	ventry	SErrorStub

	/* From EL0_64 */
	ventry	UnexpectedStub
	ventry	UnexpectedStub
	ventry	UnexpectedStub
	ventry	UnexpectedStub

	/* from EL0_32 */
	ventry	UnexpectedStub
	ventry	UnexpectedStub
	ventry	UnexpectedStub
	ventry	UnexpectedStub

/*
 * Abort stubs
 */
	stub	UnexpectedStub,		EXCEPTION_UNEXPECTED
	stub	SynchronousStub,	EXCEPTION_SYNCHRONOUS
	stub	SErrorStub,		EXCEPTION_SYSTEM_ERROR

/*
 * IRQ stub
 */
	.globl	IRQStub
IRQStub:

	kernel_entry

	bl HandleInterrupt

	kernel_exit

	eret