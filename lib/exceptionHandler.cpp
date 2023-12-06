#include <exceptionHandler.h>
#include <interruptHandler.h>
#include <assert.h>
#include <exception.h>
#include "../kernel/kernel.h"

void HandleException (uint64_t nException, TAbortFrame *pFrame)
{
    ExceptionHandler::Throw(nException, pFrame);
}

void HandleInterrupt (void)
{
    InterruptHandler::Handle();
}

ExceptionHandler *ExceptionHandler::m_pInstance = 0;

ExceptionHandler::ExceptionHandler()
{
    assert(m_pInstance == 0);
    m_pInstance = this;
}

ExceptionHandler::~ExceptionHandler()
{
    m_pInstance = 0;
}
__attribute__((optimize(0)))
void ExceptionHandler::Throw(uint64_t nException, TAbortFrame *pFrame)
{
    Kernel::m_pInstance->m_miniUART << (char*)"Exception: " << nException ;
    Kernel::m_pInstance->m_miniUART.putChar('\n');
    
    // Branch to the address contained in pFrame->elr_el1
    asm volatile("br %0" : : "r"(pFrame->elr_el1));
}