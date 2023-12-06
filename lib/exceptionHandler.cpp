#include <exceptionHandler.h>
#include <interruptHandler.h>

void HandleException (uint64_t nException, TAbortFrame *pFrame)
{
    /// just HANG for now
    __asm__ volatile ("b HandleException");
}

void HandleInterrupt (void)
{
    InterruptHandler::Handle();
}