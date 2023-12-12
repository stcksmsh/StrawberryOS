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


struct __attribute__ ((packed)) ESR_EL1
{
	uint64_t	iss:25,
	/// @brief instruction length for synchronous exceptions, 0 for 16-bit, 1 for 32-bit, set to 1 for SErrors, Instruction Aborts, PC alignment faults, Data Abort for ISV set to 0, Illegal Execution state, any DEBUG except for breakpoint, any for EC = 0
				il:1,
	/// @brief exception class, see docs/exceptions.md for more information
	#define UNKNOWN_EXCEPTION	0b000000
	#define SVC64_EXCEPTION		0b010101
				ec:6,
				iss2:24,
				res:8;
};


struct __attribute__ ((packed)) TAbortFrame
{
	/// @brief  exception syndrome register
	ESR_EL1	esr_el1;
	/// @brief saved program status register
	uint64_t	spsr_el1;
	/// @brief link register
	uint64_t	x30;
	/// @brief exception link register, the return address
	uint64_t	elr_el1;
	/// @brief stack pointer for EL0
	uint64_t	sp_el0;
	/// @brief stack pointer for EL1
	uint64_t	sp_el1;
	/// @brief fault address register
	uint64_t	far_el1;
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