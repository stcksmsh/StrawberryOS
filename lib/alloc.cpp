#include <alloc.h>
#include <memoryManager.h>
#include <util.h>

void *malloc(size_t nSize)
{
    return MemoryManager::heapAllocate(nSize);
}

void free(void *pAddress)
{
    MemoryManager::heapFree(pAddress);
}

void *calloc(size_t nSize, size_t nCount)
{
    void *pAddress = malloc(nSize * nCount);
    memset(pAddress, 0, nSize * nCount);
    return pAddress;
}

void *realloc(void *pAddress, size_t nSize)
{
    return MemoryManager::heapReallocate(pAddress, nSize);
}

void *palloc()
{
    return MemoryManager::pageAllocate();
}

void pfree(void *pAddress)
{
    MemoryManager::pageFree(pAddress);
}