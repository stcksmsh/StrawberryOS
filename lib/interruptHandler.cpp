/**
 * @file interruptHandler.cpp
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
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
    /// disable arm timer for core 0
    write32(ARM_LOCAL_TIMER_CNTRL0, 0);
    write32(ARM_LOCAL_PMU_CONTROL_CLR, ~0x0);
}


void InterruptHandler::Handle()
{
    uint32_t nCPUID;
    __asm__ volatile("mrs %0, mpidr_el1" : "=r" (nCPUID));
    nCPUID &= 0x3;
    Kernel::m_pInstance->m_miniUART << (char*)"CPU ID: ";
    Kernel::m_pInstance->m_miniUART.printHex(nCPUID);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nIRQSource = read32(ARM_LOCAL_IRQ_SOURCE0);
    Kernel::m_pInstance->m_miniUART << (char*)"ARM_LOCAL_IRQ_SOURCE0: ";
    Kernel::m_pInstance->m_miniUART.printHex(nIRQSource);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nFIQSource = read32(ARM_LOCAL_FIQ_SOURCE0);
    Kernel::m_pInstance->m_miniUART << (char*)"ARM_LOCAL_FIQ_SOURCE0: ";
    Kernel::m_pInstance->m_miniUART.printHex(nFIQSource);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nIRQStatus0 = read32(ARMC_IRQ_STATUS0);
    Kernel::m_pInstance->m_miniUART << (char*)"IRQ_STATUS0: ";
    Kernel::m_pInstance->m_miniUART.printHex(nIRQStatus0);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nIRQStatus1 = read32(ARMC_IRQ_STATUS1);
    Kernel::m_pInstance->m_miniUART << (char*)"IRQ_STATUS1: ";
    Kernel::m_pInstance->m_miniUART.printHex(nIRQStatus1);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nIRQStatus2 = read32(ARMC_IRQ_STATUS2);
    Kernel::m_pInstance->m_miniUART << (char*)"IRQ_STATUS2: ";
    Kernel::m_pInstance->m_miniUART.printHex(nIRQStatus2);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nFIQPending0 = read32(ARMC_FIQ0_PENDING0);
    Kernel::m_pInstance->m_miniUART << (char*)"FIQ0_PENDING0: ";
    Kernel::m_pInstance->m_miniUART.printHex(nFIQPending0);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nFIQPending1 = read32(ARMC_FIQ0_PENDING1);
    Kernel::m_pInstance->m_miniUART << (char*)"FIQ0_PENDING1: ";
    Kernel::m_pInstance->m_miniUART.printHex(nFIQPending1);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nFIQPending2 = read32(ARMC_FIQ0_PENDING2);
    Kernel::m_pInstance->m_miniUART << (char*)"FIQ0_PENDING2: ";
    Kernel::m_pInstance->m_miniUART.printHex(nFIQPending2);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nIRQPending0 = read32(ARMC_IRQ0_PENDING0);
    Kernel::m_pInstance->m_miniUART << (char*)"IRQ0_PENDING0: ";
    Kernel::m_pInstance->m_miniUART.printHex(nIRQPending0);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nIRQPending1 = read32(ARMC_IRQ0_PENDING1);
    Kernel::m_pInstance->m_miniUART << (char*)"IRQ0_PENDING1: ";
    Kernel::m_pInstance->m_miniUART.printHex(nIRQPending1);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nIRQPending2 = read32(ARMC_IRQ0_PENDING2);
    Kernel::m_pInstance->m_miniUART << (char*)"IRQ0_PENDING2: ";
    Kernel::m_pInstance->m_miniUART.printHex(nIRQPending2);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nLocalTimerControl = read32(ARM_TIMER_CONTROL);
    Kernel::m_pInstance->m_miniUART << (char*)"ARM_TIMER_CONTROL: ";
    Kernel::m_pInstance->m_miniUART.printHex(nLocalTimerControl);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nLocalTimerRawIrq = read32(ARM_TIMER_RAWIRQ);
    Kernel::m_pInstance->m_miniUART << (char*)"ARM_TIMER_RAWIRQ: ";
    Kernel::m_pInstance->m_miniUART.printHex(nLocalTimerRawIrq);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nSysTimerControl = read32(ARM_SYSTIMER_CS);
    Kernel::m_pInstance->m_miniUART << (char*)"ARM_SYSTIMER_CS: ";
    Kernel::m_pInstance->m_miniUART.printHex(nSysTimerControl);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nISR_EL1;
    __asm__ volatile("mrs %0, spsr_el1" : "=r" (nISR_EL1));
    Kernel::m_pInstance->m_miniUART << (char*)"ISR_EL1: ";
    Kernel::m_pInstance->m_miniUART.printHex(nISR_EL1);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    uint32_t nTimerCntrl0 = read32(ARM_LOCAL_TIMER_CNTRL0);
    Kernel::m_pInstance->m_miniUART << (char*)"ARM_LOCAL_TIMER_CNTRL0: ";
    Kernel::m_pInstance->m_miniUART.printHex(nTimerCntrl0);
    Kernel::m_pInstance->m_miniUART.putChar('\n');

    DisableIRQs();
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
    uintptr_t aEnableRegister = ARMC_IRQ0_SET_EN_0 + (ARMC_IRQ1_SET_EN_0 - ARMC_IRQ0_SET_EN_0) * nCpuId + (nIRQ / 32) * 4;
    regSet(aEnableRegister, 1, 1, nIRQ % 32);
}

void InterruptHandler::DisableIRQ(size_t nIRQ, size_t nCpuId)
{
    assert(nIRQ < IRQ_LINES);
    uintptr_t aEnableRegister = ARMC_IRQ0_CLR_EN_0 + (ARMC_IRQ1_CLR_EN_0 - ARMC_IRQ0_CLR_EN_0) * nCpuId + (nIRQ / 32) * 4;
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