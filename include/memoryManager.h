/**
 * @file memoryManager.h
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief main memory management class, contains other simpler classes
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <memorymap.h>
#include <heapAllocator.h>
#include <pageAllocator.h>
#include <translationTable.h>

class MemoryManager
{
public:
    MemoryManager(bool bEnableMMU);
    ~MemoryManager();

    /// get remaining memory
    static size_t getMemorySize();

    /// get the specified coherent memory page
    static void* getCoherentPage(uint8_t u8Slot);

    /// allocate, prefers HIGH memory
    static void* heapAllocate(size_t nSize);

    /// reallocate, prefers HIGH memory
    static void* heapReallocate(void* pMem, size_t nSize);

    /// free memory
    static void heapFree(void* pMem);

    /// allocate a page
    static void* pageAllocate();

    /// free a page
    static void pageFree(void* pMem);

private:
    /// enable Memory Management Unit
    void EnableMMU();

    /// is the MMU enabled?
    bool m_bEnableMMU;

    /// heap allocator for LOW memory
    HeapAllocator m_HeapLow;

    /// heap allocator for HIGH memory
    HeapAllocator m_HeapHigh;

    /// page allocator
    PageAllocator m_Pager;

    /// translation table
    TranslationTable m_pTranslationTable;
    
    /// singleton instance
    static MemoryManager *m_pInstance;
};

#endif  // MEMORY_MANAGER_H