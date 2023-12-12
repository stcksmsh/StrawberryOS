#include <exceptionHandler.h>
#include <interruptHandler.h>
#include <assert.h>
#include <exception.h>
#include "../kernel/kernel.h"

const char* msgs[] = {(char*)"UNEXPECTED", (char*)"SYNCHRONOUS", (char*)"SERROR"};

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
    if(nException == EXCEPTION_SYNCHRONOUS && pFrame->esr_el1.ec == SVC64_EXCEPTION){ /// SVC from arch64
        ESR_EL1 exception = pFrame->esr_el1;
        // Kernel::m_pInstance->m_miniUART <<  (char*)msgs[nException] << (char*)": << exception;
        Kernel::m_pInstance->m_miniUART.print(exception.iss);
        Kernel::m_pInstance->m_miniUART.putChar('\n');
    }
    // Branch to the address contained in pFrame->elr_el1
    asm volatile("br %0" : : "r"(pFrame->elr_el1));
}