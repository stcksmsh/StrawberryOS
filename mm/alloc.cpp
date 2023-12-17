/**
 * @file alloc.cpp
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief some simple memory allocation functions, will be removed in the future
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
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