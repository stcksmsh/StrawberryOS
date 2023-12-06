/*
 *	exceptionHandler.h
 *
 *  stcksmsh[github.com] - vukicevickosta@gmail.com
 *
 * 	exception/interrupt handler functions
 */

#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

#include <types.h>
struct __attribute__ ((packed)) TAbortFrame
{
	uint64_t	esr_el1;	// exception syndrome register
	uint64_t	spsr_el1;	// saved program status register
	uint64_t	x30;		// link register
	uint64_t	elr_el1;	// exception link register, the return address
	uint64_t	sp_el0;		// stack pointer for EL0
	uint64_t	sp_el1;		// stack pointer for EL1
	uint64_t	far_el1;	// fault address register
	uint64_t	unused;
};

extern "C"{
    void HandleException (uint64_t u64Exception, TAbortFrame *pFrame);
    void HandleInterrupt (void);
};


class ExceptionHandler
{
public:
    static void Throw(uint64_t nException, TAbortFrame *pFrame);

private:
    ExceptionHandler();
    ~ExceptionHandler();

	static ExceptionHandler *m_pInstance;

	friend class Kernel;
};


#endif // EXCEPTION_HANDLER_H