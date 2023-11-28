#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include <memorymap.hpp>
#include <heapAllocator.hpp>
#include <pageAllocator.hpp>

class MemoryManager
{
public:
    MemoryManager();
    ~MemoryManager();

    /// initialize the memory manager
    static MemoryManager *get();

    /// get remaining memory
    size_t getMemorySize();

    /// allocate, prefers HIGH memory
    static void* heapAllocate(size_t size);

private:
    /// enable Memory Management Unit
    void EnableMMU();

    /// is the MMU enabled?
    bool m_bEnableMMU;

    /// memory size for LOW portion
    size_t m_lMemSizeLow;
    
    /// memory size for HIGH portion
    size_t m_lMemSizeHigh;

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