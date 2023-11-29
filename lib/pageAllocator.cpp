#include <pageAllocator.h>
#include <sysconfig.h>
#include <assert.h>

PageAllocator::PageAllocator():
    m_u8Head(0),
    m_u8Tail(0){
}

PageAllocator::~PageAllocator(){
}

void PageAllocator::init(uintptr_t aStart, size_t nSize){
    m_u8Head = (uint8_t*)((aStart + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1));
    m_u8Tail = (uint8_t*)((aStart + nSize) & ~(PAGE_SIZE - 1));
}

size_t PageAllocator::getFreeMemory() const{
    return m_u8Tail - m_u8Head;
}

void *PageAllocator::pageAllocate(){
    assert(m_u8Head != 0);
    PageHeader *pNewPage = m_pFreePages;
    if(pNewPage != 0){
        assert(pNewPage->m_u32PageMagic == PAGE_MAGIC);
        m_pFreePages = pNewPage->m_pNext;
        pNewPage->m_u32PageMagic = 0;
    }else{
        pNewPage = (PageHeader*)m_u8Head;
        
        m_u8Head += PAGE_SIZE;
        
        if(m_u8Head >= m_u8Tail){
            assert(false); /// ran out of memory
        }
    }
    return pNewPage;
}

void PageAllocator::pageFree(void *ptr){
    assert(m_u8Head != 0);

    PageHeader *pNewPage = (PageHeader*)ptr;

    pNewPage->m_pNext = m_pFreePages;
    pNewPage->m_u32PageMagic = PAGE_MAGIC;
    m_pFreePages = pNewPage;
}