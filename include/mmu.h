/*
 *  mmu.h
 *
 *  stcksmsh[github.com] - vukicevickosta@gmail.com
 *
 *  Declaratons meant to be used with granule size 4KB and 48 bit OA
 *  
 *  Information used gathered from: Arm Architecture Reference Manual Armv8, for Armv8-A architecture profile, D8, D8.3 Translation Table Descriptor formats, page 5852
 */

#ifndef MMU_H
#define MMU_H

#include <types.h>


#define MMU_GRANULE_SIZE		0x1000		// 4KB
#define MMU_TABLE_ENTRIES		512         // 512 entries per table

// level 0
struct L0_TABLE_DESCRIPTOR{
    uint64_t    Valid       :1,     // set  to 1
                Type        :1,     // set to 1, table entry
                Ignored1    :10,    // set to 0, not important
                TableAddr   :36,    // L1 table base address [47:12]
                Reserved    :3,     // set to 0
                Ignored2    :8,     // set to 0
                PXNTable         :1,     // Privileged eXecute Never, 1 means that the memory region is NOT executable in privileged mode (EL1\2\3), should be 0?
                UXNTable         :1,     // Unprivileged eXecute Never, should be 0 where the memory region is executable in unprivileged mode (EL0) (in EL2 or EL3 it is the XN, eXecute Never bit)
                APTable          :2,     // Access Permissions, in privileged mode (EL1\2\3) reading is enabled , and if byte 1 is unset, then write is enabled in privileged mode
                                    // bit 0 controlls access in unprivileged mode (EL0), and if byte 1 is unset, then write is enabled in unprivileged mode
                                    // if bit 0 is unset, then there is no read or write access in unprivileged mode
                NSTable     :1;     // next table is Non-Secure, always 0 for now
}__attribute__((packed));

// level 1
struct L1_TABLE_DESCRIPTOR{
    uint64_t    Valid       :1,     // set  to 1
                Type        :1,     // set to 1, table entry
                Ignored1    :10,    // set to 0, not important
                TableAddr   :36,    // L2 table base address [47:12]
                Reserved    :3,     // set to 0
                Ignored2    :8,     // set to 0
                PXNTable         :1,     // Privileged eXecute Never, 1 means that the memory region is NOT executable in privileged mode (EL1\2\3), should be 0?
                UXNTable         :1,     // Unprivileged eXecute Never, should be 0 where the memory region is executable in unprivileged mode (EL0) (in EL2 or EL3 it is the XN, eXecute Never bit)
                APTable          :2,     // Access Permissions, in privileged mode (EL1\2\3) reading is enabled , and if byte 1 is unset, then write is enabled in privileged mode
                                    // bit 0 controlls access in unprivileged mode (EL0), and if byte 1 is unset, then write is enabled in unprivileged mode
                                    // if bit 0 is unset, then there is no read or write access in unprivileged mode
                NSTable     :1;     // next table is Non-Secure, always 0 for now
}__attribute__((packed));

/// 1 GB block
struct L1_BLOCK_DESCRIPTOR{
    uint64_t    Valid       :1,     // set  to 1
                Type        :1,     // set to 0, block entry
                AttrIndx    :3,     // Memory Attributes Index, 0b000 is normal memory, 0b001 is device memory, 0b010 is non-cacheable memory
                NS          :1,     // Non-Secure, always 0 for now
                AP          :2,     // Access Permissions, in privileged mode (EL1\2\3) reading is enabled , and if byte 1 is unset, then write is enabled in privileged mode
                                    // bit 0 controlls access in unprivileged mode (EL0), and if byte 1 is unset, then write is enabled in unprivileged mode
                                    // if bit 0 is unset, then there is no read or write access in unprivileged mode
                SH          :2,     // Shareability, 0b10 is Outer Shareable, 0b11 is Inner Shareable
                AF          :1,     // Access Flag, set to 1
                nG          :1,     // not Global, set to 1
                Reserved0   :18,     // set to 0
                OutputAddr  :18,    // Output Address [47:21]
                Reserved1   :2,     // set to 0
                GP          :1,     // Guarded Page, set to 0
                DBM         :1,     // Dirty Bit Modifier, set to 0
                Contiguous  :1,     // set to 0
                PXN         :1,     // Privileged eXecute Never, 1 means that the memory region is NOT executable in privileged mode (EL1\2\3), should be 0? (in EL2 or EL3 it is the XN, eXecute Never bit)
                UXN         :1,     // Unprivileged eXecute Never, should be 0 where the memory region is executable in unprivileged mode (EL0)
                Ignored     :4,     // set to 0
                PBHA        :4,     // Page Based Hardware Attributes, set to 0
                Reserved2   :1;
}__attribute__((packed));

struct L1_INVALID_DESCRIPTOR{
    uint64_t    Valid       :1,     // set to 0b1
                Ignored     :63;    // set to 0
}__attribute__((packed));

union L1_DESCRIPTOR{
    struct L1_TABLE_DESCRIPTOR     Table;
    struct L1_BLOCK_DESCRIPTOR     Block;
    struct L1_INVALID_DESCRIPTOR   Invalid;
}__attribute__((packed));

// level 2
struct L2_TABLE_DESCRIPTOR{
    uint64_t    Valid       :1,     // set  to 1
                Type        :1,     // set to 1, table entry
                Ignored1    :10,    // set to 0, not important
                TableAddr   :36,    // L2 table base address [47:12]
                Reserved0   :3,     // set to 0
                Ignored2    :8,     // set to 0
                Reserved1   :5;     // next table is Non-Secure, always 0 for now
}__attribute__((packed));

/// 2 MB block
struct L2_BLOCK_DESCRIPTOR{
    uint64_t    Valid       :1,     // set  to 1
                Type        :1,     // set to 0, block entry
                MemAttr     :3,     // Memory Attributes Index, 0b000 is normal memory, 0b001 is device memory, 0b010 is non-cacheable memory
                S2AP        :2,     // Access Permissions, in privileged mode (EL1\2\3) reading is enabled , and if byte 1 is unset, then write is enabled in privileged mode
                SH          :2,     // Shareability, 0b10 is Outer Shareable, 0b11 is Inner Shareable
                AF          :1,     // Access Flag, set to 1
                nG          :1,     // not Global, set to 1
                nT          :1,     // not Translation Table, set to 0
                Reserved0   :9,     // set to 0
                OutputAddr  :29,    // Output Address [49:21]
                GP          :1,     // Guarded Page, set to 0
                DBM         :1,     // Dirty Bit Modifier, set to 0
                Contiguous  :1,     // set to 0
                PXN         :1,     // Privileged eXecute Never, 1 means that the memory region is NOT executable in privileged mode (EL1\2\3), should be 0? (in EL2 or EL3 it is the XN, eXecute Never bit)
                UXN         :1,     // Unprivileged eXecute Never, should be 0 where the memory region is executable in unprivileged mode (EL0)
                NS          :1,     // Non-Secure, always 0 for now
                Ignored     :3,     // set to 0
                PBHA        :4,     // Page Based Hardware Attributes, set to 0
                Reserved2   :1;     // set to 0
}__attribute__((packed));

struct L2_INVALID_DESCRIPTOR{
    uint64_t    Valid       :1,     // set to 0b1
                Ignored     :63;    // set to 0
}__attribute__((packed));

union L2_DESCRIPTOR{
    struct L2_TABLE_DESCRIPTOR     Table;
    struct L2_BLOCK_DESCRIPTOR     Block;
    struct L2_INVALID_DESCRIPTOR   Invalid;
}__attribute__((packed));


// level 3
/// 4 KB Page
struct L3_PAGE_DESCRIPTOR{
    uint64_t    Valid       :1,     // set  to 1
                Type        :1,     // set to 0, page entry
                MemAttr     :3,     // Memory Attributes Index, 0b000 is normal memory, 0b001 is device memory, 0b010 is non-cacheable memory
                NS          :1,     // Non-Secure, always 0 for now
                AP          :2,     // Access Permissions, in privileged mode (EL1\2\3) reading is enabled , and if byte 1 is unset, then write is enabled in privileged mode
                                    // bit 0 controlls access in unprivileged mode (EL0), and if byte 1 is unset, then write is enabled in unprivileged mode
                                    // if bit 0 is unset, then there is no read or write access in unprivileged mode
                SH          :2,     // Shareability, 0b10 is Outer Shareable, 0b11 is Inner Shareable
                AF          :1,     // Access Flag, set to 1
                nG          :1,     // not Global, set to 1
                OutputAddr  :36,    // Output Address [47:12]
                Reserved1   :4,     // set to 0
                Contiguous  :1,     // set to 0
                PXN         :1,     // Privileged eXecute Never, 1 means that the memory region is NOT executable in privileged mode (EL1\2\3), should be 0? (in EL2 or EL3 it is the XN, eXecute Never bit)
                UXN         :1,     // Unprivileged eXecute Never, should be 0 where the memory region is executable in unprivileged mode (EL0)
                Reserved2   :4,     // set to 0
                Ignored     :5;     // set to 0
}__attribute__((packed));

struct L3_INVALID_DESCRIPTOR{
    uint64_t    Valid       :1,     // set to 0b1
                Ignored     :63;    // set to 0
}__attribute__((packed));

union L3_DESCRIPTOR{
    struct L3_PAGE_DESCRIPTOR     Page;
    struct L3_INVALID_DESCRIPTOR   Invalid;
}__attribute__((packed));




#endif // MMU_H