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

};

#endif // TRANSLATION_TABLE_H