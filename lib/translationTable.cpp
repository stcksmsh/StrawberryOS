#include <translationTable.h>
#include <alloc.h>
#include <util.h>
#include <assert.h>
#include <memorymap.h>


TranslationTable::TranslationTable(){}


void TranslationTable::init(size_t nSize)
{
    /// Allocate memory for the L0 table and zero it
    m_pTable = (L1_TABLE_DESCRIPTOR *)palloc();
    assert(m_pTable != 0);
    memset(m_pTable, 0, PAGE_SIZE);
    for( int i = 0; i < 100; i ++){
        m_pTable->Valid = 1;
        m_pTable->Type = 1;
        m_pTable->TableAddr = (uintptr_t)createL2Table(i * 2 * MEGABYTE) >> 12;
        m_pTable->PXNTable = 0;
        m_pTable->UXNTable = 0;
        m_pTable->APTable = 0b00;
        m_pTable->NSTable = 0;
        m_pTable ++;
    }

    // /// Invalidate all entries
    // for(int entry = 0; entry < MMU_TABLE_ENTRIES; entry++)
    // {
    //     m_pTable[entry].Valid = 0;
    // }
}


TranslationTable::~TranslationTable()
{
    // for(int entry = 0; entry < MMU_TABLE_ENTRIES; entry++)
    // {
    //     /// Get the L1 table address from the L0 table
    //     L1_TABLE_DESCRIPTOR *pL1Table = (L1_TABLE_DESCRIPTOR *)(m_pTable[entry].TableAddr << 12);

    //     for(int entry = 0; entry < MMU_TABLE_ENTRIES; entry++)
    //     {
    //         /// Get the L2 table address from the L1 table
    //         L2_TABLE_DESCRIPTOR *pL2Table = (L2_TABLE_DESCRIPTOR *)(pL1Table[entry].TableAddr << 12);

    //         for(int entry = 0; entry < MMU_TABLE_ENTRIES; entry++)
    //         {
    //             /// Get the L3 table address from the L2 table
    //             L3_PAGE_DESCRIPTOR *pL3Page = (L3_PAGE_DESCRIPTOR *)(pL2Table[entry].TableAddr << 12);
    //             /// Free the L3 table
    //             pfree(pL3Page);
    //         }

    //         /// Free the L2 table
    //         pfree(pL2Table);
    //     }

    //     /// Free the L1 table
    //     pfree(pL1Table);
    // }
    // pfree(m_pTable);
}


uintptr_t TranslationTable::getBaseAddress() const
{
    return (uintptr_t)m_pTable;
}


L2_DESCRIPTOR *TranslationTable::createL2Table(uintptr_t nBaseAddress)
{
    /// Allocate memory for the L2 table and zero it
    L2_DESCRIPTOR *pL2Desc = (L2_DESCRIPTOR *)palloc();
    assert(pL2Desc != 0);
    memset(pL2Desc, 0, PAGE_SIZE);

    L2_BLOCK_DESCRIPTOR *pL2Block = &pL2Desc->Block;
    pL2Block->Valid = 1;
    pL2Block->Type = 0;
    pL2Block->MemAttr = MAIR_NORMAL_WB;
    pL2Block->S2AP = 0b00;
    pL2Block->OutputAddr = nBaseAddress >> 12;


    // L2_TABLE_DESCRIPTOR *pL2Table = &pL2Desc->Table;

    // for(int entry = 0; entry < MMU_TABLE_ENTRIES; entry++)
    // {
    //     /// Create L3 table
    //     L3_PAGE_DESCRIPTOR *pL3Page = &createL3Table(nBaseAddress + entry * PAGE_SIZE * MMU_TABLE_ENTRIES)->Page;
    //     assert(pL3Page != 0);

    //     /// Set the L3 table address in the L2 table
    //     pL2Table[entry].Valid = 1;
    //     pL2Table[entry].Type = 1;
    //     pL2Table[entry].TableAddr = (uintptr_t)pL3Page >> 12;
    // }

    return pL2Desc;
}

L3_DESCRIPTOR *TranslationTable::createL3Table(uintptr_t nBaseAddress)
{
    /// Allocate memory for the L3 table and zero it
    L3_DESCRIPTOR *pL3Desc = (L3_DESCRIPTOR *)palloc();
    assert(pL3Desc != 0);
    memset(pL3Desc, 0, PAGE_SIZE);
    // L3_PAGE_DESCRIPTOR *pL3Page = &pL3Desc->Page;

    // for(int entry = 0; entry < MMU_TABLE_ENTRIES; entry++)
    // {
    //     /// Set the L3 table address in the L3 table
    //     pL3Page[entry].Valid = 1;
    //     pL3Page[entry].Type = 1;
    //     pL3Page[entry].OutputAddr = (nBaseAddress + entry * PAGE_SIZE) >> 12;
    // }

    return pL3Desc;
}