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

InterruptHandler *InterruptHandler::m_pInstance = 0;
IRQ_handler *InterruptHandler::m_pIRQHandlers[IRQ_LINES] = {0};

InterruptHandler::InterruptHandler()
{
    for(int i = 0; i < IRQ_LINES; i++)
    {
        m_pIRQHandlers[i] = 0;
    }
    if(m_pInstance == 0)
    {
        m_pInstance = this;
    }
}

void InterruptHandler::Handle()
{
    uint32_t irq2 = mmioRead(IRQ0_PENDING2);
    
    if(irq2 & (1 << 24)){ /// OR of low 32
        uint32_t irq0 = mmioRead(IRQ0_PENDING0);

        for(int i = 0; i < 32; i++)
        {
            if(irq0 & (1 << i))
            {
                if(m_pIRQHandlers[i] != 0)
                {
                    m_pIRQHandlers[i](0);
                }
                else
                {
                    /// UNHANDLED IRQ
                }
            }
        }

    }

    if(irq2 & (1 << 25)){ /// OR of high 32
        uint32_t irq1 = mmioRead(IRQ1_PENDING0);
        for(int i = 0; i < 32; i++)
        {
            if(irq1 & (1 << i))
            {
                if(m_pIRQHandlers[i+32] != 0)
                {
                    m_pIRQHandlers[i+32](0);
                }
                else
                {
                    /// UNHANDLED IRQ
                }
            }
        }
    }
    
}

void InterruptHandler::RegisterIRQ(uint8_t nIRQ, IRQ_handler *pHandler, void *pParam)
{
    assert(nIRQ < IRQ_LINES);
    m_pIRQHandlers[nIRQ] = pHandler;
}

void InterruptHandler::UnregisterIRQ(uint8_t nIRQ)
{
    assert(nIRQ < IRQ_LINES);
    m_pIRQHandlers[nIRQ] = 0;
}

void InterruptHandler::EnableIRQ(uint8_t nIRQ)
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

void InterruptHandler::DisableIRQ(uint8_t nIRQ)
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
    }}
