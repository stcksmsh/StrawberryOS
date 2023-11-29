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