#ifndef heapAllocator_H
#define heapAllocator_H

#include <memorymap.h>
#include <types.h>

struct SimpleHeapHeader{
    SimpleHeapHeader* pNext;
    SimpleHeapHeader* pPrev;
    size_t nSize;
    uint32_t u32Magic;
#define HEAP_BLOCK_MAGIC	0x424C4D43
};

class HeapAllocator{

public:
    HeapAllocator();

    ~HeapAllocator();

    /// initialize the heap allocator
    void init(uintptr_t nStart, size_t nSize);

    /// get the size of the heap
    size_t getHeapFreeMemory();

    /// allocate memory from the heap
    void* heapAllocate(size_t nSize);

    /// reallocate memory from the heap
    void* heapReallocate(void* pAddress, size_t nSize);

    /// free memory from the heap
    void heapFree(void* pAddress);

private:
    
    /// pointer to the start/end of the heap
    SimpleHeapHeader *m_pHead, *m_pTail;
};




#endif  // heapAllocator_H