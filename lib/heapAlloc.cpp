#include <heapAllocator.hpp>
#include <assert.hpp>
#include <util.hpp>

HeapAllocator* HeapAllocator::m_pInstance = nullptr;

HeapAllocator::HeapAllocator(){
    if(m_pInstance == nullptr){
        m_pInstance = this;
    }
}

HeapAllocator::~HeapAllocator(){
    if(m_pInstance == this){
        m_pInstance = nullptr;
    }
}

void HeapAllocator::init(uintptr_t nStart, size_t nSize){
    m_pHead = reinterpret_cast<SimpleHeapHeader*>(nStart);
    m_pHead->nMagic = HEAP_BLOCK_MAGIC;
    m_pHead->nSize = nSize - sizeof(SimpleHeapHeader);
    m_pHead->pNext = nullptr;
    m_pHead->pPrev = nullptr;
    m_pHead->free = true;
    m_pTail = m_pHead;
}

size_t HeapAllocator::getHeapFreeMemory(){
    // size_t nFreeMemory = 0;
    SimpleHeapHeader* pCurrent = m_pInstance->m_pHead;
    // while(pCurrent != nullptr){
    //     assert(pCurrent->nMagic == HEAP_BLOCK_MAGIC);
    //     nFreeMemory += pCurrent->nSize;
    //     pCurrent = pCurrent->pNext;
    // }
    // return nFreeMemory;
    return pCurrent -> nSize;
}

void* HeapAllocator::heapAllocate(size_t nSize){
    SimpleHeapHeader* pCurrent = m_pInstance->m_pHead;
    while(pCurrent != nullptr){
        assert(pCurrent->nMagic == HEAP_BLOCK_MAGIC);
        assert(pCurrent->free);
        if(pCurrent->nSize >= nSize){
            if(pCurrent->nSize > nSize + sizeof(SimpleHeapHeader)){
                SimpleHeapHeader* pNewBlock = reinterpret_cast<SimpleHeapHeader*>(reinterpret_cast<size_t>(pCurrent) + sizeof(SimpleHeapHeader) + nSize);
                pNewBlock->nMagic = HEAP_BLOCK_MAGIC;
                pNewBlock->nSize = pCurrent->nSize - nSize - sizeof(SimpleHeapHeader);
                pNewBlock->pNext = pCurrent->pNext;
                pNewBlock->pPrev = pCurrent;
                if(pCurrent->pNext != nullptr){
                    pCurrent->pNext->pPrev = pNewBlock;
                }
                pCurrent->pNext = pNewBlock;
                pCurrent->nSize = nSize;
            }
            if(pCurrent->pPrev){
                pCurrent->pPrev->pNext = pCurrent->pNext;
            }
            if(pCurrent->pNext){
                pCurrent->pNext->pPrev = pCurrent->pPrev;
            }
            if(m_pInstance->m_pTail == pCurrent){
                m_pInstance->m_pTail = pCurrent -> pPrev;
            }
            if(m_pInstance->m_pHead == pCurrent){
                m_pInstance->m_pHead = pCurrent->pNext;
            }
            pCurrent -> free = false;
            return reinterpret_cast<void*>(reinterpret_cast<size_t>(pCurrent) + sizeof(SimpleHeapHeader));
        }
        pCurrent = pCurrent->pNext;
    }
    return nullptr;
}

void* HeapAllocator::heapReAllocate(void* pAddress, size_t nSize){
    SimpleHeapHeader* pCurrent = reinterpret_cast<SimpleHeapHeader*>(reinterpret_cast<uintptr_t>(pAddress) - sizeof(SimpleHeapHeader));
    assert(pCurrent->nMagic == HEAP_BLOCK_MAGIC);
    assert(pCurrent->free);
    if(pCurrent->nSize >= nSize){
        if(pCurrent->nSize > nSize + sizeof(SimpleHeapHeader)){
            SimpleHeapHeader* pNewBlock = reinterpret_cast<SimpleHeapHeader*>(reinterpret_cast<uintptr_t>(pCurrent) + sizeof(SimpleHeapHeader) + nSize);
            pNewBlock->nMagic = HEAP_BLOCK_MAGIC;
            pNewBlock->nSize = pCurrent->nSize - nSize - sizeof(SimpleHeapHeader);
            pNewBlock->pNext = pCurrent->pNext;
            pNewBlock->pPrev = pCurrent;
            if(pCurrent->pNext != nullptr){
                pCurrent->pNext->pPrev = pNewBlock;
            }
            pCurrent->pNext = pNewBlock;
            pCurrent->nSize = nSize;
        }
        return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pCurrent) + sizeof(SimpleHeapHeader));
    }
    else{
        void* pNewAddress = heapAllocate(nSize);
        if(pNewAddress != nullptr){
            memcpy(pNewAddress, pAddress, pCurrent->nSize);
            heapFree(pAddress);
        }
        return pNewAddress;
    }
}

void HeapAllocator::heapFree(void* pAddress){
    SimpleHeapHeader *pCurrent = reinterpret_cast<SimpleHeapHeader*>(reinterpret_cast<uintptr_t>(pAddress) - sizeof(SimpleHeapHeader));
    assert(pCurrent->nMagic == HEAP_BLOCK_MAGIC);
    /// find the right place to insert
    SimpleHeapHeader *node = pCurrent -> pNext;
    pCurrent->free = true;
    while(node && !node->free){
        assert(node->nMagic == HEAP_BLOCK_MAGIC);
        node = node ->pNext;
    }
    if(m_pInstance->m_pHead == nullptr){
        m_pInstance->m_pHead = m_pInstance->m_pTail = pCurrent;
        pCurrent->pPrev = pCurrent->pNext = nullptr;
    }else if(!node){
        node = m_pInstance->m_pTail;
        node->pNext = pCurrent;
        pCurrent->pPrev = node;
        pCurrent->pNext = nullptr;
        m_pInstance->m_pTail = pCurrent;
    }else{
        pCurrent->pPrev = node->pPrev;
        pCurrent->pNext = node;
        node->pPrev = pCurrent;
    }

    /// merge with next block
    if(pCurrent -> pNext && 
        reinterpret_cast<size_t>(pCurrent) + pCurrent->nSize ==
        reinterpret_cast<size_t>(pCurrent -> pNext)){
        pCurrent -> nSize += pCurrent -> pNext -> nSize + sizeof(SimpleHeapHeader);
        pCurrent -> pNext = pCurrent -> pNext -> pNext;
        pCurrent -> pNext -> pPrev = pCurrent;
    }

    /// merge with previous block
    if(pCurrent -> pPrev &&
        reinterpret_cast<size_t>(pCurrent -> pPrev) + pCurrent -> pPrev -> nSize ==
        reinterpret_cast<size_t>(pCurrent)){
        pCurrent -> pPrev -> nSize += pCurrent -> nSize + sizeof(SimpleHeapHeader);
        pCurrent -> pPrev -> pNext = pCurrent -> pNext;
        pCurrent -> pNext -> pPrev = pCurrent -> pPrev;
    }
}

HeapAllocator* HeapAllocator::get(){
    return m_pInstance;
}