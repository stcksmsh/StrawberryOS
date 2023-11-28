#ifndef EXCEPTION_HANDLER_HPP
#define EXCEPTION_HANDLER_HPP

#include <types.hpp>
struct TAbortFrame
{
	uint64_t	esr_el1;
	uint64_t	spsr_el1;
	uint64_t	x30;
	uint64_t	elr_el1;
	uint64_t	sp_el0;
	uint64_t	sp_el1;
	uint64_t	far_el1;
	uint64_t	unused;
};__attribute__ ((packed))

extern "C"{
    void ExceptionHandler (uint64_t nException, TAbortFrame *pFrame);
    void InterruptHandler (void);
};


#endif
