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

/* Indices in the MAIR register */
#define MAIR_NORMAL_WB 0        /// inner/outer write-back, non-transient, allocating
/// ATTR_INDX_Normal(ATTR_INDX_Normal_policy(0b0,0b1,0b1,0b1), ATTR_INDX_Normal_policy(0b0,0b1,0b1,0b1))
#define MAIR_DEVICE_nGnRE 1     /// non-gathering, non-reordering, early-acknowledgement
/// ATTR_INDX_Device_nGnRE
#define MAIR_DEVICE_nGnRnE 2    /// non-gathering, non-reordering, non-early-acknowledgement
/// ATTR_INDX_Device_nGnRnE
#define MAIR_NORMAL_WT 3        /// inner/outer write-through, non-transient, allocating
/// ATTR_INDX_Normal(ATTR_INDX_Normal_policy(0b0,0b0,0b1,0b1), ATTR_INDX_Normal_policy(0b0,0b1,0b0,0b0))
#define MAIR_NORMAL_NC 4        /// inner/outer non-cacheable
/// ATTR_INDX_Normal(ATTR_INDX_Normal_policy(0b0,0b1,0b0,0b0), ATTR_INDX_Normal_policy(0b0,0b1,0b0,0b0))


#define ATTRINDX_NORMAL MAIR_NORMAL_WB
#define ATTRINDX_DEVICE MAIR_DEVICE_nGnRE
#define ATTRINDX_COHERENT MAIR_DEVICE_nGnRnE

class TranslationTable
{
public:
    TranslationTable();
    ~TranslationTable();

    uintptr_t getBaseAddress() const;

    void init(size_t nSize);

private:
    L2_DESCRIPTOR *createL2Table(uintptr_t nBaseAddress);
    L3_DESCRIPTOR *createL3Table(uintptr_t nBaseAddress);

private:
    size_t m_nMemSize;

    L1_TABLE_DESCRIPTOR *m_pTable;
};

#endif // TRANSLATION_TABLE_H