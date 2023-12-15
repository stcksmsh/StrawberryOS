/*
 *  interruptHandler.h
 *  
 *  stcksmsh[github.com] - vukicevickosta@gmail.com
 * 
 * InterruptHandler class for IRQ handling
 */

#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include <types.h>
#include <interrupt.h>


typedef void IRQ_handler (void *pParam);

class InterruptHandler
{
public:
    static void Handle();
    static void RegisterIRQ(size_t nIRQ, IRQ_handler *pHandler, void *pParam);
    static void UnregisterIRQ(size_t nIRQ);
    static void EnableIRQ(size_t nIRQ, size_t nCpuId = 0);
    static void DisableIRQ(size_t nIRQ, size_t nCpuId = 0);

    static void EnableIRQs();
    static void DisableIRQs();

private:

    InterruptHandler();


    static void *m_pParams[IRQ_LINES];         
    static IRQ_handler *m_pIRQHandlers[IRQ_LINES];
    static InterruptHandler *m_pInstance;

    friend class Kernel;
};

#endif // INTERRUPT_HANDLER_H