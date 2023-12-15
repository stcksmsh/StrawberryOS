/*
 * interrupt.cpp
 *
 * stcksmsh[github.com] - vukicevickosta@gmail.com
 * 
 * InterruptHandler class for IRQ handling source file
 */

#include <interruptHandler.h>
#include <exception.h>
#include <assert.h>
#include <mmio.h>
#include <bcm2711.h>
#include "../kernel/kernel.h"

InterruptHandler *InterruptHandler::m_pInstance = 0;
IRQ_handler *InterruptHandler::m_pIRQHandlers[IRQ_LINES] = {0};
void *InterruptHandler::m_pParams[IRQ_LINES] = {0};

InterruptHandler::InterruptHandler()
{
    if(m_pInstance == 0)
    {
        m_pInstance = this;
    }
}


void InterruptHandler::Handle()
{
    uint32_t nIRQSource = mmioRead(IRQ_SOURCE0);
    Kernel::m_pInstance->m_miniUART << (char*)"IRQ source: ";
    Kernel::m_pInstance->m_miniUART.printHex(nIRQSource);
    Kernel::m_pInstance->m_miniUART.putChar('\n');
}

void InterruptHandler::RegisterIRQ(size_t nIRQ, IRQ_handler *pHandler, void *pParam)
{
    assert(nIRQ < IRQ_LINES);
    m_pIRQHandlers[nIRQ] = pHandler;
    m_pParams[nIRQ] = pParam;
}

void InterruptHandler::UnregisterIRQ(size_t nIRQ)
{
    assert(nIRQ < IRQ_LINES);
    m_pIRQHandlers[nIRQ] = 0;
}

void InterruptHandler::EnableIRQ(size_t nIRQ, size_t nCpuId)
{
    assert(nIRQ < IRQ_LINES);
    uintptr_t aEnableRegister = IRQ0_SET_EN_0 + (IRQ1_SET_EN_0 - IRQ0_SET_EN_0) * nCpuId + (nIRQ / 32) * 4;
    regSet(aEnableRegister, 1, 1, nIRQ % 32);
}

void InterruptHandler::DisableIRQ(size_t nIRQ, size_t nCpuId)
{
    assert(nIRQ < IRQ_LINES);
    uintptr_t aEnableRegister = IRQ0_CLR_EN_0 + (IRQ1_CLR_EN_0 - IRQ0_CLR_EN_0) * nCpuId + (nIRQ / 32) * 4;
    regSet(aEnableRegister, 1, 1, nIRQ % 32);
    
}


void InterruptHandler::EnableIRQs()
{
    __asm__ volatile("msr daifclr, #2");
}

void InterruptHandler::DisableIRQs()
{
    __asm__ volatile("msr daifset, #2");
}