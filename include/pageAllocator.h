/*
 * pageAllocator.h
 *
 * stcksmsh[github.com] - vukicevickosta@gmail.com
 * 
 * PageAllocator class for allocating pages
 */

#ifndef PAGE_ALLOCATOR_H
#define PAGE_ALLOCATOR_H

#include <types.h>

class PageAllocator
{
public:
    PageAllocator();
    ~PageAllocator();

    /// initialize the page allocator
    void init(uintptr_t aStart, size_t nSize);

    /// get available memory
    size_t getFreeMemory() const;

    /// allocate a page
    void *pageAllocate();

    /// free a page
    void pageFree(void *ptr);
private:
    uint8_t *m_u8Head;
    uint8_t *m_u8Tail;  

    struct PageHeader
    {
        uint32_t m_u32PageMagic;
        #define PAGE_MAGIC 0x07AF8F54
        PageHeader *m_pNext;
    } *m_pFreePages;
};

#endif  // PAGE_ALLOCATOR_H