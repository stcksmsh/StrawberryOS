#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

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
    static void* heapAllocate(size_t size);

    /// reallocate, prefers HIGH memory
    static void* heapReallocate(void* pMem, size_t size);

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

#endif