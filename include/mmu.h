/**
 * @file mmu.h
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
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
                OutputAddr  :18,    // Output Address [47:30]
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
                Reserved1   :5;     // No attributes for L2
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
                OutputAddr  :27,    // Output Address [47:21]
                Reserved1   :2,     // set to 0
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



/* AttrIndx definitions */

/// Meaning of gathering - gathering means that the processor can combine multiple memory accesses into a single transaction
/// Meaning of reordering - reordering means that the processor can reorder memory accesses, non-reordering means that accesses within the same block must appear in program order
/// Meaning of early write acknowledgement - early write acknowledgement means that the processor can acknowledge a write before the write has been completed

// Non-gathering, non-reordering, non-early write acknowledgement
#define ATTR_INDX_Device_nGnRnE 0b00000000
// Non-gathering, non-reordering, early write acknowledgement
#define ATTR_INDX_Device_nGnRE  0b00000001
// Non-gathering, reordering, early write acknowledgement
#define ATTR_INDX_Device_nGRE   0b00000010
// Gathering, reordering, early write acknowledgement
#define ATTR_INDX_Device_GRE     0b00000100

/// Meaning of transience - transience means that the memory region is transient, meaning that the memory region is not expected to be used for long periods of time
/// Meaning of through-back - through-back means that the memory region is a write trough region, meaning that writes to the memory region are not cached
/// Meaning of read allocation - read allocation means that the memory region is read-allocate, meaning that reads to the memory region are cached

/// Format is 0bOOOOIIII where O is outer policy and I is inner policy, see 'ATTR_INDX_Normal_policy' for how OOOO or IIII is coded
/// Inner policy refers to the L1 cache and outer to L2 (if it exists)
#define ATTR_INDX_Normal(outer, inner) static_cast<uint64_t>(0b00000000 | \
((outer & 0xf) << 4) | \
(inner & 0xf))

/// Used for OOOO and IIII encoding, meaning of bits:
/// bit 3: Transience, 0b0 means the memory region is not transient, 0b1 means the memory region is transient
/// bit 2: Through-back, 0b0 means the memory region is not a write trough region, 0b1 means the memory region is a write back region
/// bit 1: Read allocation, 0b0 means the memory region is read non-allocate, 0b1 means the memory region is read-allocate
/// bit 0: Write allocation, 0b0 means the memory region is write non-allocate, 0b1 means the memory region is write-allocate
/// Some special cases:
///     0b0000 is not allowed
///     0b0100 is for non-cacheable memory
#define ATTR_INDX_Normal_policy(transience, through_back, read_alloc, write_alloc) 0b0000 | \
(   (transience & 0b1) << 3    ) | \
(   (through_back & 0b1) << 2  ) | \
(   (read_alloc & 0b1) << 1    ) | \
(   (write_alloc & 0b1) << 0   )


/// There exists a few more possible configurations based on certain system flags, but they are note used in this project (at least for now)
/// If i do use them this will be amended


/* TCR_ELn definitions */
// See page 7071 for more information on TCRL_EL1
// See page 7086 for more information on TCRL_EL2
// See page 7106 for more information on TCRL_EL3

struct TCR_ELn{
    uint64_t    TOSZ:   6,
                Res0:   1,
                EPD0:   1,
                IRGN0:   2,
                ORGN0:  2,
                SH0:    2,
                TG0:    2,
                T1SZ:   6,
                A1:     1,
                EPD1:   1,
                IRGN1:  2,
                ORGN1:  2,
                SH1:    2,
                TG1:    2,
                IPS:    3,
                Res1:   1,
                AS:     1,
                TBI0:   1,
                TBI1:   1,
                HA:     1,
                HD:     1,
                HPD0:   1,
                HPD1:   1,
                HWU059: 1,
                HWU060: 1,
                HWU061: 1,
                HWU062: 1,
                HWU159: 1,
                HWU160: 1,
                HWU161: 1,
                HWU162: 1,
                TBID0:  1,
                TBID1:  1,
                NFD0:   1,
                NFD1:   1,
                E0PD0:   1,
                E0PD1:   1,
                TCMA0:  1,
                TCMA1:  1,
                DS:     1,
                Res2:   4;
}__attribute__((packed));

union mmu_tcr{
    TCR_ELn tcr_eln;
    uint64_t raw;
};


#endif // MMU_H