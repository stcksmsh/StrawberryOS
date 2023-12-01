/*
 *  translationTable.h
 *
 *  stcksmsh[github.com] - vukicevickosta@gmail.com
 * 
 * Translation Table class for managing the translation table
 */

#ifndef TRANSLATION_TABLE_H
#define TRANSLATION_TABLE_H

#include <types.h>
#include <mmu.h>

class TranslationTable
{
public:
    TranslationTable(size_t nSize);
    ~TranslationTable();

    uintptr_t getBaseAddress() const;

private:
    L1_DESCRIPTOR *createL1Table(uintptr_t nBaseAddress);
    L2_DESCRIPTOR *createL2Table(uintptr_t nBaseAddress);
    L3_DESCRIPTOR *createL3Table(uintptr_t nBaseAddress);

private:
    size_t m_nMemSize;

    L0_TABLE_DESCRIPTOR *m_pTable;
};

#endif // TRANSLATION_TABLE_H