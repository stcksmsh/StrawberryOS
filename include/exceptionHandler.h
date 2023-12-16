/**
 * @file exceptionHandler.h
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

#include <types.h>

/** @struct ESR_EL1
 * @brief Exception Syndrome Register, used to determine the cause of the exception
 */
/** @var ESR_EL1::iss
 * @brief instruction specific syndrome, see docs/exceptions.md for more information
 */
/** @var ESR_EL1::il
 * instruction length for synchronous exceptions, 0 for 16-bit, 1 for 32-bit, set to 1 for SErrors, Instruction Aborts, PC alignment faults, Data Abort for ISV set to 0, Illegal Execution state, any DEBUG except for breakpoint, any for EC = 0
 */
/** @var ESR_EL1::ec
 * exception class, see docs/exceptions.md for more information
 */
/** @var ESR_EL1::iss2
 */
/** @var ESR_EL1::res
 */
#define UNKNOWN_EXCEPTION				0b000000
#define ILLEGAL_STATE_EXCEPTION			0b001110
/// @brief SVC instruction from 32bit state
#define SVC32_EXCEPTION					0b010001
/// @brief SVC instruction from 64bit state
#define SVC64_EXCEPTION					0b010101
/// @brief Instruction Abort from a lower Exception level
#define INSTRUCTION_ABORT_LEL_EXCEPTION	0b100000 
/// @brief Instruction Abort from the current Exception level
#define INSTRUCTION_ABORT_SEL_EXCEPTION	0b100001 

struct __attribute__ ((packed)) ESR_EL1
{
	uint64_t	iss:25,
	/// instruction length for synchronous exceptions, 0 for 16-bit, 1 for 32-bit, set to 1 for SErrors, Instruction Aborts, PC alignment faults, Data Abort for ISV set to 0, Illegal Execution state, any DEBUG except for breakpoint, any for EC = 0
				il:1,
	/// exception class, see docs/exceptions.md for more information
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