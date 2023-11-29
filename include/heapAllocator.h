/*
 *	heapAllocator.h
 *
 *  stcksmsh[github.com] - vukicevickosta@gmail.com
 *
 * 	Heap allocator class
 */

#ifndef heapAllocator_H
#define heapAllocator_H

#include <memorymap.h>
#include <types.h>

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
    struct HeapBlockHeader{
        HeapBlockHeader* pNext;
        HeapBlockHeader* pPrev;
        size_t nSize;
        uint32_t u32Magic;
    #define HEAP_BLOCK_MAGIC	0x19DAC0DE
    } *m_pHead, *m_pTail;
    /// pointer to the start/end of the heap
};




#endif  // heapAllocator_H