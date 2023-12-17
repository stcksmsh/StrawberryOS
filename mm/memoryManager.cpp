/**
 * @file memoryManager.cpp
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief implementation of the MemoryManager class, the main memory management class in the kernel
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <memoryManager.h>
#include <machineinfo.h>
#include <sysconfig.h>
#include <assert.h>
#include <util.h>

MemoryManager *MemoryManager::m_pInstance = 0;

MemoryManager::MemoryManager(bool bEnableMMU):
    m_bEnableMMU(bEnableMMU)
{
    if(m_pInstance == 0){
        m_pInstance = this;
    }

    uint64_t memSizeLow = MEM_HEAP_SIZE;
    m_HeapLow.init(MEM_HEAP_START, memSizeLow);

    size_t memSizeHigh = MachineInfo::getMemSize();
    if(memSizeHigh <= MEM_HIGHMEM_START){
        memSizeHigh = 0;
    }else{
        memSizeHigh -= MEM_HIGHMEM_START;
    }
    m_HeapHigh.init(MEM_HIGHMEM_START, memSizeHigh);

    if(m_bEnableMMU){
        m_pTranslationTable.init(200 * MEGABYTE);
        EnableMMU();
    }
}

MemoryManager::~MemoryManager(){
    m_pInstance = 0;
}

size_t MemoryManager::getMemorySize()
{
    return m_pInstance->m_HeapLow.getHeapFreeMemory() + m_pInstance->m_HeapHigh.getHeapFreeMemory();
}

void *MemoryManager::heapAllocate(size_t size)
{
    void *pMem = m_pInstance->m_HeapHigh.heapAllocate(size);
    if(pMem == 0)
        pMem = m_pInstance->m_HeapLow.heapAllocate(size);
    return pMem;
}

void* MemoryManager::heapReallocate(void* pMem, size_t size)
{
    void *pNewMem = heapAllocate(size);
    memcpy(pNewMem, pMem, size);
    heapFree(pMem);

    return pNewMem;
}

void MemoryManager::heapFree(void* pMem)
{
    if(reinterpret_cast<uintptr_t>(pMem) >= MEM_HIGHMEM_START){
        m_pInstance->m_HeapHigh.heapFree(pMem);
    }else{
        m_pInstance->m_HeapLow.heapFree(pMem);
    }
}

void MemoryManager::EnableMMU()
{
    assert(m_bEnableMMU);

    // Set MAIR
    uint64_t mair = 0;
    ///  see translationTable.h for more information on theses values
    mair |= (ATTR_INDX_Normal(ATTR_INDX_Normal_policy(0b0,0b1,0b1,0b1), ATTR_INDX_Normal_policy(0b0,0b1,0b1,0b1)) \
            << MAIR_NORMAL_WB * 8); /// inner/outer write-back, non-transient, allocating
    mair |= (ATTR_INDX_Device_nGnRE << MAIR_DEVICE_nGnRE * 8); /// non-gathering, non-reordering, early-acknowledgement
    mair |= (ATTR_INDX_Device_nGnRnE << MAIR_DEVICE_nGnRnE * 8); /// non-gathering, non-reordering, non-early-acknowledgement
    mair |= (ATTR_INDX_Normal(ATTR_INDX_Normal_policy(0b0,0b0,0b1,0b1), ATTR_INDX_Normal_policy(0b0,0b1,0b0,0b0)) \
            << MAIR_NORMAL_WT * 8);/// inner/outer write-through, non-transient, allocating
    mair |= (ATTR_INDX_Normal(ATTR_INDX_Normal_policy(0b0,0b1,0b0,0b0), ATTR_INDX_Normal_policy(0b0,0b1,0b0,0b0)) \
            << (MAIR_NORMAL_NC * 8)); /// inner/outer non-cacheable
    
    asm volatile("msr mair_el1, %0" : : "r"(mair)); 

    /// set the translation table base address
    assert(m_pInstance->m_pTranslationTable.getBaseAddress() != 0);
    asm volatile("msr ttbr0_el1, %0" : : "r"(m_pInstance->m_pTranslationTable.getBaseAddress()));

    /// set the translation control register
    mmu_tcr tcr;
    tcr.raw = 0;
    /// make unprivileged access generate Level0 faults
    tcr.tcr_eln.E0PD0 = 1;
    /// set granularity to 4KB
    tcr.tcr_eln.TG0 = 0b00;
    /// make it inner-shareable
    tcr.tcr_eln.SH0 = 0b11;
    /// Outer - normal write-back, read-allocate, write-allocate cachable
    tcr.tcr_eln.ORGN0 = 0b01;
    /// Inner - normal write-back, read-allocate, write-allocate cachable
    tcr.tcr_eln.IRGN0 = 0b01;
    /// set Intermediate Physical Address Size to 36 bits
    tcr.tcr_eln.IPS = 0b001;
    /// size offset of memory region
    tcr.tcr_eln.TOSZ = 28;

    asm volatile("msr tcr_el1, %0" : : "r"(tcr.raw));
    asm volatile("isb");

#define SCTLR_EL1_WXN		(1 << 19)		// SCTLR_EL1
#define SCTLR_EL1_I		(1 << 12)
#define SCTLR_EL1_C		(1 << 2)
#define SCTLR_EL1_A		(1 << 1)
#define SCTLR_EL1_M		(1 << 0)


    uint64_t nSCTLR_EL1;
	asm volatile ("mrs %0, sctlr_el1" : "=r" (nSCTLR_EL1));
	nSCTLR_EL1 &= ~(  SCTLR_EL1_WXN
			| SCTLR_EL1_A);
	nSCTLR_EL1 |=   SCTLR_EL1_I
		      | SCTLR_EL1_C
		      | SCTLR_EL1_M;
	// asm volatile ("msr sctlr_el1, %0" : : "r" (nSCTLR_EL1));
    // asm volatile("isb");
}

void *MemoryManager::getCoherentPage(uint8_t u8Slot)
{
    if(u8Slot >= 32)
        return 0;
    return reinterpret_cast<void*>(MEM_COHERENT_REGION + u8Slot * PAGE_SIZE);
}

void *MemoryManager::pageAllocate()
{
    return m_pInstance->m_Pager.pageAllocate();
}

void MemoryManager::pageFree(void *pMem)
{
    m_pInstance->m_Pager.pageFree(pMem);
}