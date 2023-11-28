#ifndef PAGE_ALLOCATOR_HPP
#define PAGE_ALLOCATOR_HPP

#include <types.hpp>

class PageAllocator
{
public:
    PageAllocator();
    ~PageAllocator();

    /// initialize the page allocator
    void Setup(uintptr_t start, uintptr_t end);

    /// get available memory
    size_t getFreeMemory();

    /// allocate a page
    void *allocate(size_t size);

    /// free a page
    void free(void *ptr);
};

#endif