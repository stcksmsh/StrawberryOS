/**
 * @file heapAllocator.cpp
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <heapAllocator.h>
#include <assert.h>
#include <util.h>

HeapAllocator::HeapAllocator(){
}

HeapAllocator::~HeapAllocator(){
    
}

void HeapAllocator::init(uintptr_t nStart, size_t nSize){
    if(nSize == 0){
        m_pHead = 0;
        m_pTail = 0;
        return;
    }
    m_pHead = reinterpret_cast<HeapBlockHeader*>(nStart);
    m_pHead->u32Magic = HEAP_BLOCK_MAGIC;
    m_pHead->nSize = nSize - sizeof(HeapBlockHeader);
    m_pHead->pNext = 0;
    m_pHead->pPrev = 0;
    m_pTail = m_pHead;
}

size_t HeapAllocator::getHeapFreeMemory(){
    size_t nFreeMemory = 0;
    HeapBlockHeader* pCurrent = m_pHead;
    while(pCurrent != 0){
        assert(pCurrent->u32Magic == HEAP_BLOCK_MAGIC);
        nFreeMemory += pCurrent->nSize;
        pCurrent = pCurrent->pNext;
    }
    return nFreeMemory;
}

void* HeapAllocator::heapAllocate(size_t nSize){
    HeapBlockHeader* pCurrent = m_pHead;
    while(pCurrent != 0){
        assert(pCurrent->u32Magic == HEAP_BLOCK_MAGIC);
        if(pCurrent->nSize >= nSize){
            if(pCurrent->nSize > nSize + sizeof(HeapBlockHeader)){
                HeapBlockHeader* pNewBlock = reinterpret_cast<HeapBlockHeader*>(reinterpret_cast<size_t>(pCurrent) + sizeof(HeapBlockHeader) + nSize);
                pNewBlock->u32Magic = HEAP_BLOCK_MAGIC;
                pNewBlock->nSize = pCurrent->nSize - nSize - sizeof(HeapBlockHeader);
                pNewBlock->pNext = pCurrent->pNext;
                pCurrent->pNext = pNewBlock;
                pCurrent->nSize = nSize;
            }
            if(pCurrent->pNext != 0){
                pCurrent->pNext->pPrev = pCurrent->pPrev;
            }
            if(pCurrent->pPrev != 0){
                pCurrent->pPrev->pNext = pCurrent->pNext;
            }
            if(pCurrent == m_pHead){
                m_pHead = pCurrent->pNext;
            }
            if(pCurrent == m_pTail){
                m_pTail = pCurrent->pPrev;
            }
            return reinterpret_cast<void*>(reinterpret_cast<size_t>(pCurrent) + sizeof(HeapBlockHeader));
        }
        pCurrent = pCurrent->pNext;
    }
    return 0;
}

void* HeapAllocator::heapReallocate(void* pAddress, size_t nSize){
    if(m_pHead == 0){
        return 0;
    } 
    HeapBlockHeader *pCurrent = reinterpret_cast<HeapBlockHeader*>(reinterpret_cast<uintptr_t>(pAddress) - sizeof(HeapBlockHeader));
    assert(pCurrent->u32Magic == HEAP_BLOCK_MAGIC);
    
    HeapBlockHeader *pSearch = m_pHead;
    while(pSearch != 0 && pSearch < pCurrent){
        pSearch = pSearch -> pNext;
    }

    if(pSearch != 0 && pCurrent + pCurrent -> nSize == pSearch && pCurrent -> nSize + pSearch -> nSize + sizeof(HeapBlockHeader) >= nSize){
        size_t nBytesTaken = nSize - pCurrent -> nSize;
        pSearch -> nSize -= nBytesTaken;
        HeapBlockHeader *pNewBlock = reinterpret_cast<HeapBlockHeader*>(reinterpret_cast<uintptr_t>(pSearch) + nBytesTaken);
        pNewBlock -> u32Magic = HEAP_BLOCK_MAGIC;
        pNewBlock -> nSize = pSearch -> nSize;
        pNewBlock -> pNext = pSearch -> pNext;
        pNewBlock -> pPrev = pSearch -> pPrev;
        if(pNewBlock -> pNext)
            pNewBlock -> pNext -> pPrev = pNewBlock;
        if(pNewBlock -> pPrev)
            pNewBlock -> pPrev -> pNext = pNewBlock;
        pCurrent -> nSize = nSize;
        pCurrent -> pNext = pSearch -> pNext;
        pCurrent -> pNext -> pPrev = pCurrent;
    }else{
        void *pNewAddress = heapAllocate(nSize);
        if(pNewAddress == 0){
            return 0;
        }
        memcpy(pNewAddress, pAddress, pCurrent -> nSize);
        heapFree(pAddress);
        pAddress = pNewAddress;
    }
    return pAddress;
}

void HeapAllocator::heapFree(void* pAddress){
    if(m_pHead == 0){
        return;
    }
    HeapBlockHeader *pCurrent = reinterpret_cast<HeapBlockHeader*>(reinterpret_cast<uintptr_t>(pAddress) - sizeof(HeapBlockHeader));
    assert(pCurrent->u32Magic == HEAP_BLOCK_MAGIC);
    /// find the right place to insert
    HeapBlockHeader *pInsert = m_pHead;
    while(pInsert != 0 && pInsert < pCurrent){
        pInsert = pInsert -> pNext;
    }

    /// insert
    if(pInsert == 0){
        pCurrent -> pNext = 0;
        pCurrent -> pPrev = m_pTail;
        m_pTail -> pNext = pCurrent;
        m_pTail = pCurrent;
    }else{
        pCurrent -> pNext = pInsert;
        pCurrent -> pPrev = pInsert -> pPrev;
        pInsert -> pPrev = pCurrent;
        if(pCurrent -> pPrev){
            pCurrent -> pPrev -> pNext = pCurrent;
        }else{
            m_pHead = pCurrent;
        }
    }

    /// merge with next block
    if(pCurrent -> pNext && 
        reinterpret_cast<size_t>(pCurrent) + pCurrent->nSize ==
        reinterpret_cast<size_t>(pCurrent -> pNext)){
        pCurrent -> nSize += pCurrent -> pNext -> nSize + sizeof(HeapBlockHeader);
        pCurrent -> pNext = pCurrent -> pNext -> pNext;
        pCurrent -> pNext -> pPrev = pCurrent;
    }

    /// merge with previous block
    if(pCurrent -> pPrev &&
        reinterpret_cast<size_t>(pCurrent -> pPrev) + pCurrent -> pPrev -> nSize ==
        reinterpret_cast<size_t>(pCurrent)){
        pCurrent -> pPrev -> nSize += pCurrent -> nSize + sizeof(HeapBlockHeader);
        pCurrent -> pPrev -> pNext = pCurrent -> pNext;
        pCurrent -> pNext -> pPrev = pCurrent -> pPrev;
    }

    /// I seem to be losing memory somewhere
    /// it seems to happen on every allocation
    /// this stays untill i figure out why
    pCurrent -> nSize += sizeof(HeapBlockHeader);
}
