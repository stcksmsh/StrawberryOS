#ifndef heapAllocator_HPP
#define heapAllocator_HPP

#include <memorymap.hpp>
#include <types.hpp>

struct SimpleHeapHeader{
    uint32_t nMagic;
#define HEAP_BLOCK_MAGIC	0x424C4D43
    size_t nSize;
    SimpleHeapHeader* pNext;
    SimpleHeapHeader* pPrev;
    bool free;
};

class HeapAllocator{

public:
    HeapAllocator();

    ~HeapAllocator();

    /// initialize the heap allocator
    void init(uintptr_t nStart, size_t nSize);

    /// get the size of the heap
    static size_t getHeapFreeMemory();

    /// allocate memory from the heap
    static void* heapAllocate(size_t nSize);

    /// reallocate memory from the heap
    static void* heapReAllocate(void* pAddress, size_t nSize);

    /// free memory from the heap
    static void heapFree(void* pAddress);

    /// get the heap allocator instance
    static HeapAllocator* get(); 

private:
    /// singleton instance
    static HeapAllocator *m_pInstance;
    
    /// pointer to the start/end of the heap
    SimpleHeapHeader *m_pHead, *m_pTail;
};




#endif