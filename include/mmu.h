/*
 *  mmu.h
 *
 *  stcksmsh[github.com] - vukicevickosta@gmail.com
 *
 * 
 */

#ifndef MMU_H
#define MMU_H

#include <types.h>


#define MMU_GRANULE_SIZE		0x10000		// 64KB
#define MMU_TABLE_ENTRIES		8192


// level 2

struct MMU_LEVEL3_TABLE_DESCRIPTOR{
    uint64_t    Value       :2, // set to 0b11
                Ignored1    :14,
                TableAddr   :32, // 32 bit table base address [47-16]
                Reserved    :4, // set to 0b0000
                Ignored2    :7, // set to 0b0000000
                PXNTable    :1, // set to 0b0
                UXNTable    :1, // set to 0b0
                APTable     :2,
    #define AP_TABLE_ALL_ACCESS     0x0
                NSTable     :1; //  set to 0b0
};


#endif // MMU_H