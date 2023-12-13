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

    InitializeGIC();
}

void InterruptHandler::InitializeGIC(){

}

void InterruptHandler::Handle()
{
    // Kernel::m_pInstance->m_miniUART << (char*)"IRQ";
    // Kernel::m_pInstance->m_miniUART.putChar('\n');

    // store IRQ number in variable called nIRQ
    uint32_t nIRQ0 = mmioRead(IRQ0_PENDING0);
    // uint32_t nIRQ1 = mmioRead(IRQ0_PENDING1);
    // uint32_t nIRQ2 = mmioRead(IRQ0_PENDING2);

    // Kernel::m_pInstance->m_miniUART.putChar('\n');
    // Kernel::m_pInstance->m_miniUART.printHex(nIRQ0);
    // Kernel::m_pInstance->m_miniUART.putChar('\n');
    // Kernel::m_pInstance->m_miniUART.printHex(nIRQ1);
    // Kernel::m_pInstance->m_miniUART.putChar('\n');
    // Kernel::m_pInstance->m_miniUART.printHex(nIRQ2);
    // Kernel::m_pInstance->m_miniUART.putChar('\n');

    // now just close the IRQ
    if(nIRQ0 == IRQ_TIMER_0){
        m_pIRQHandlers[nIRQ0](m_pParams[nIRQ0]);
    }
    mmioWrite(IRQ0_PENDING0, nIRQ0);
    return;

    // uint32_t irq2 = mmioRead(IRQ0_PENDING2);
    
    // if(irq2 & (1 << 24)){ /// OR of low 32
    //     uint32_t irq0 = mmioRead(IRQ0_PENDING0);

    //     for(int i = 0; i < 32; i++)
    //     {
    //         if(irq0 & (1 << i))
    //         {
    //             if(m_pIRQHandlers[i] != 0)
    //             {
    //                 m_pIRQHandlers[i](m_pParams[i]);
    //             }
    //             else
    //             {
    //                 /// UNHANDLED IRQ
    //             }
    //         }
    //     }

    // }

    // if(irq2 & (1 << 25)){ /// OR of high 32
    //     uint32_t irq1 = mmioRead(IRQ1_PENDING0);
    //     for(int i = 0; i < 32; i++)
    //     {
    //         if(irq1 & (1 << i))
    //         {
    //             if(m_pIRQHandlers[i+32] != 0)
    //             {
    //                 m_pIRQHandlers[i+32](0);
    //             }
    //             else
    //             {
    //                 /// UNHANDLED IRQ
    //             }
    //         }
    //     }
    // }
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
    if(nIRQ < 32)
    {
        regSet(IRQ0_SET_EN_0, 1, 1, nIRQ);
    }
    else if(nIRQ < 64)
    {
        regSet(IRQ0_SET_EN_1, 1, 1, nIRQ - 32);
    }else{
        regSet(IRQ0_SET_EN_2, 1, 1, nIRQ - 64);
    }
}

void InterruptHandler::DisableIRQ(size_t nIRQ)
{
assert(nIRQ < IRQ_LINES);
    if(nIRQ < 32)
    {
        regSet(IRQ0_CLR_EN_0, 1, 1, nIRQ);
    }
    else if(nIRQ < 64)
    {
        regSet(IRQ0_CLR_EN_1, 1, 1, nIRQ - 32);
    }else{
        regSet(IRQ0_CLR_EN_2, 1, 1, nIRQ - 64);
    }
}
