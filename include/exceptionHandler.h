#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H

#include <types.h>
struct __attribute__ ((packed)) TAbortFrame
{
	uint64_t	esr_el1;
	uint64_t	spsr_el1;
	uint64_t	x30;
	uint64_t	elr_el1;
	uint64_t	sp_el0;
	uint64_t	sp_el1;
	uint64_t	far_el1;
	uint64_t	unused;
};

extern "C"{
    void ExceptionHandler (uint64_t u64Exception, TAbortFrame *pFrame);
    void InterruptHandler (void);
};


#endif // EXCEPTION_HANDLER_H