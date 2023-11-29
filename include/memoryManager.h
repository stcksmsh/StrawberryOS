#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <memorymap.h>
#include <heapAllocator.h>
#include <pageAllocator.h>

class MemoryManager
{
public:
    MemoryManager(bool bEnableMMU);
    ~MemoryManager();

    /// get remaining memory
    static size_t getMemorySize();

    /// allocate, prefers HIGH memory
    static void* heapAllocate(size_t nSize);

    /// reallocate, prefers HIGH memory
    static void* heapReallocate(void* pMem, size_t nSize);

    /// free memory
    static void heapFree(void* pMem);

private:
    /// enable Memory Management Unit
    void EnableMMU();

    /// is the MMU enabled?
    bool m_bEnableMMU;

    /// heap allocator for LOW memory
    HeapAllocator m_HeapLow;

    /// heap allocator for HIGH memory
    HeapAllocator m_HeapHigh;

    /// page allocator
    PageAllocator m_Pager;
    
    /// singleton instance
    static MemoryManager *m_pInstance;
};

#endif  // MEMORY_MANAGER_H