#ifndef PAGE_ALLOCATOR_H
#define PAGE_ALLOCATOR_H

#include <types.h>

class PageAllocator
{
public:
    PageAllocator();
    ~PageAllocator();

    /// initialize the page allocator
    void Setup(uintptr_t aStart, uintptr_t aEnd);

    /// get available memory
    size_t getFreeMemory();

    /// allocate a page
    void *allocate(size_t nSize);

    /// free a page
    void free(void *ptr);
};

#endif  // PAGE_ALLOCATOR_H