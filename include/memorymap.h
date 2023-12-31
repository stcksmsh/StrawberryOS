/**
 * @file memorymap.h
 * @author stcksmsh (stcksmsh@gmail.com)
 * @brief contains memory map constants
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef MEMORYMAP_H
#define MEMORYMAP_H


#ifndef KILOBYTE
    #define KILOBYTE	0x400
#endif
#ifndef MEGABYTE
	#define MEGABYTE	0x100000
#endif
#ifndef GIGABYTE
	#define GIGABYTE	0x40000000ULL
#endif

#define MEM_SIZE (1 * GIGABYTE)
#define GPU_MEM_SIZE (76 * MEGABYTE)
#define ARM_MEM_SIZE (MEM_SIZE - GPU_MEM_SIZE)

#define PAGE_SIZE (4 * KILOBYTE)

#define EXCEPTION_STACK_SIZE (32 * KILOBYTE)
#define PAGE_TABLE1_SIZE	0x4000
#define PAGE_RESERVE		(16 * MEGABYTE)

#ifndef CORES
#define CORES			4					// must be a power of 2
#endif

#define MEM_KERNEL_START	0x80000
#define MEM_KERNEL_END		(MEM_KERNEL_START + KERNEL_MAX_SIZE)
#define MEM_KERNEL_STACK	(MEM_KERNEL_END + KERNEL_STACK_SIZE)		// expands downwards
#define MEM_EXCEPTION_STACK	(MEM_KERNEL_STACK + KERNEL_STACK_SIZE * (CORES-1) + EXCEPTION_STACK_SIZE)
#define MEM_EXCEPTION_STACK_END	(MEM_EXCEPTION_STACK + EXCEPTION_STACK_SIZE * (CORES-1))

// coherent memory region (4 MB)
#define MEM_COHERENT_REGION	((MEM_EXCEPTION_STACK_END + MEGABYTE) & ~(MEGABYTE-1))

#define MEM_HEAP_START		(MEM_COHERENT_REGION + 4*MEGABYTE)
#define MEM_HEAP_SIZE 		(ARM_MEM_SIZE - MEM_HEAP_START - PAGE_RESERVE)

// high memory region (memory >= 3 GB is not safe to be DMA-able and is not used)
#define MEM_HIGHMEM_START		GIGABYTE

// PCIe memory range (outbound)
#define MEM_PCIE_RANGE_START		0x600000000UL
#define MEM_PCIE_RANGE_SIZE		0x4000000UL
#define MEM_PCIE_RANGE_PCIE_START	0xF8000000UL		// mapping on PCIe side
#define MEM_PCIE_RANGE_START_VIRTUAL	MEM_PCIE_RANGE_START
#define MEM_PCIE_RANGE_END_VIRTUAL	(MEM_PCIE_RANGE_START_VIRTUAL + MEM_PCIE_RANGE_SIZE - 1UL)

// PCIe memory range (inbound)
#define MEM_PCIE_DMA_RANGE_START	0UL
#define MEM_PCIE_DMA_RANGE_SIZE		0x100000000UL
#define MEM_PCIE_DMA_RANGE_PCIE_START	0UL			// mapping on PCIe side

#endif // MEMORYMAP_H
